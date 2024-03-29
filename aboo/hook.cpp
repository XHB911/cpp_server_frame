#include "hook.h"
#include <dlfcn.h>
#include <stdarg.h>

#include "config.h"
#include "log.h"
#include "fiber.h"
#include "iomanager.h"
#include "fd_manager.h"

aboo::Logger::ptr g_logger = ABOO_LOG_NAME("system");
namespace aboo {

static aboo::ConfigVar<int>::ptr g_tcp_connect_timeout = aboo::Config::Lookup("tcp.connect.timeout", 5000, "tcp connect timeout");

static thread_local bool t_hook_enable = false;

#define HOOK_FUN(XX) \
	XX(sleep) \
	XX(usleep) \
	XX(nanosleep) \
	XX(socket) \
	XX(connect) \
	XX(accept) \
	XX(read) \
	XX(readv) \
	XX(recv) \
	XX(recvfrom) \
	XX(recvmsg) \
	XX(write) \
	XX(writev) \
	XX(send) \
	XX(sendto) \
	XX(sendmsg) \
	XX(close) \
	XX(fcntl) \
	XX(ioctl) \
	XX(getsockopt) \
	XX(setsockopt)

void hook_init() {
	static bool is_inited = false;
	if (is_inited) {
		return;
	}
#define XX(name) name ## _f = (name ## _fun)dlsym(RTLD_NEXT, #name);
	HOOK_FUN(XX);
#undef XX
}

static uint64_t s_connect_timeout = -1;

struct _HookIniter {
	_HookIniter() {
		hook_init();
		s_connect_timeout = g_tcp_connect_timeout->getValue();

		g_tcp_connect_timeout->addListener([](const int& old_value, const int& new_value) {
			ABOO_LOG_INFO(g_logger) << "tcp connect timeout changed from " << old_value << " to "<< new_value;
			s_connect_timeout = new_value;
		});
	}
};

static _HookIniter s_hook_initer;

bool is_hook_enable() {
	return t_hook_enable;
}

void set_hook_enable(bool flag) {
	t_hook_enable = flag;
}

}

struct timer_info {
	int cancelled = 0;
};

/**
 * @brief accept和read/write/recv/send等IO接口的hook模板实现
 * @param[in] fd 文件描述符
 * @param[in] fun HOOK 之后的系统调用
 * @param[in] hook_fun_name，要hook的函数名
 * @param[in] event 要设置的事件
 * @param[in] timeout_so 所获取超时时间的类型，如果是READ，则返回读超时时间，否则返回写超时时间
 * @param[in] args 被hook 系统调用所需的参数
 */
template<typename OriginFun, typename ... Args>
static ssize_t do_io(int fd, OriginFun fun, const char* hook_fun_name, uint32_t event, int timeout_so, Args&&... args) {
	// 如果没有hook，则直接返回原系统调用的结果。
	if (!aboo::t_hook_enable) {
		return fun(fd, std::forward<Args>(args)...);
	}

	//ABOO_LOG_DEBUG(g_logger) << "do_io<" << hook_fun_name << ">";
	// 从文件句柄管理器中得到对应的文件句柄上下文类
	aboo::FdCtx::ptr ctx = aboo::FdMgr::getInstance()->get(fd);
	if (!ctx) {
		return fun(fd, std::forward<Args>(args)...);
	}

	// 判断当前的文件句柄是否关闭
	if (ctx->isClosed()) {
		errno = EBADF;
		return -1;
	}

	// 如果不是 socket 套接字或者用户将该文件句柄设为非阻塞，则直接返回原系统调用的结果
	if (!ctx->isSocket() || ctx->getUserNonblock()) {
		return fun(fd, std::forward<Args>(args)...);
	}

	// 获取文件句柄的超时时间
	uint64_t to = ctx->getTimeout(timeout_so);
	std::shared_ptr<timer_info> tinfo(new timer_info);

retry:
	// 重复执行原系统调用
	ssize_t n = fun(fd, std::forward<Args>(args)...);
	while (n == -1 && errno == EINTR) {
		n = fun(fd, std::forward<Args>(args)...);
	}
	if (n == -1 && errno == EAGAIN) {
		aboo::IOManager* iom = aboo::IOManager::GetThis();
		aboo::Timer::ptr timer;
		std::weak_ptr<timer_info> winfo(tinfo);

		if (to != (uint64_t)-1) {
			timer = iom->addConditionTimer(to, [winfo, fd, iom, event]() {
				auto t = winfo.lock();
				if (!t || t->cancelled) {
					return;
				}
				t->cancelled = ETIMEDOUT;
				iom->cancelEvent(fd, (aboo::IOManager::Event)(event));
			}, winfo);
		}

		int rt = iom->addEvent(fd, (aboo::IOManager::Event)(event));
		if (rt) {
			ABOO_LOG_ERROR(g_logger) << hook_fun_name << " addEvent(" << fd << ", " << event << ")";
			if (timer) {
				timer->cancel();
			}
			return -1;
		} else {
			ABOO_LOG_DEBUG(g_logger) << "do_io<" << hook_fun_name << ">";
			aboo::Fiber::YieldToHold();
			ABOO_LOG_DEBUG(g_logger) << "do_io<" << hook_fun_name << ">";
			if (timer) {
				timer->cancel();
			}
			if (tinfo->cancelled) {
				errno = tinfo->cancelled;
				return -1;
			}
			goto retry;
		}
	}

	return n;
}

extern "C" {
#define XX(name) name ## _fun name ## _f = nullptr;
	HOOK_FUN(XX)
#undef XX

unsigned int sleep(unsigned int seconds) {
	if (!aboo::t_hook_enable) {
		return sleep_f(seconds);
	}

	aboo::Fiber::ptr fiber = aboo::Fiber::GetThis();
	aboo::IOManager* iom = aboo::IOManager::GetThis();
	iom->addTimer(seconds * 1000, std::bind((void(aboo::Scheduler::*)(aboo::Fiber::ptr, int thread))&aboo::IOManager::schedule, iom, fiber, -1));
	aboo::Fiber::YieldToHold();
	return 0;
}

int usleep(useconds_t usec) {
	if (!aboo::t_hook_enable) {
		return usleep_f(usec);
	}

	aboo::Fiber::ptr fiber = aboo::Fiber::GetThis();
	aboo::IOManager* iom = aboo::IOManager::GetThis();
	iom->addTimer(usec / 1000, std::bind((void(aboo::Scheduler::*)(aboo::Fiber::ptr, int thread))&aboo::IOManager::schedule, iom, fiber, -1));
	aboo::Fiber::YieldToHold();
	return 0;
}

int nanosleep(const struct timespec *req, struct timespec *rem) {
	if (!aboo::t_hook_enable) {
		return nanosleep_f(req, rem);
	}

	int timeout_ms = req->tv_sec * 1000 + req->tv_nsec / 1000 / 1000;
	aboo::Fiber::ptr fiber = aboo::Fiber::GetThis();
	aboo::IOManager* iom = aboo::IOManager::GetThis();
	iom->addTimer(timeout_ms, std::bind(
				(void(aboo::Scheduler::*)(aboo::Fiber::ptr, int thread))&aboo::IOManager::schedule
				, iom
				, fiber
				, -1));
	aboo::Fiber::YieldToHold();
	return 0;
}

int socket(int domain, int type, int protocol) {
	if (!aboo::t_hook_enable) {
		return socket_f(domain, type, protocol);
	}
	int fd = socket_f(domain, type, protocol);
	if (fd == -1) {
		return fd;
	}
	aboo::FdMgr::getInstance()->get(fd, true);
	return fd;
}

int connect_wait_timeout(int fd, const struct sockaddr* addr, socklen_t addrlen, uint64_t timeout_ms) {
	if (!aboo::t_hook_enable) {
		return connect_f(fd, addr, addrlen);
	}
	aboo::FdCtx::ptr ctx = aboo::FdMgr::getInstance()->get(fd);
	if (!ctx || ctx->isClosed()) {
		errno = EBADF;
		return -1;
	}
	if (!ctx->isSocket()) {
		return connect_f(fd, addr, addrlen);
	}
	if (ctx->getUserNonblock()) {
		return connect_f(fd, addr, addrlen);
	}

	int n = connect_f(fd, addr, addrlen);
	if (n == 0) {
		return 0;
	} else if (n != -1 || errno != EINPROGRESS) {
		return n;
	}

	aboo::IOManager* iom = aboo::IOManager::GetThis();
	aboo::Timer::ptr timer;
	std::shared_ptr<timer_info> tinfo(new timer_info);
	std::weak_ptr<timer_info> winfo(tinfo);

	if (timeout_ms != (uint64_t)-1) {
		timer = iom->addConditionTimer(timeout_ms, [winfo, fd, iom]() {
			auto t = winfo.lock();
			if (!t || t->cancelled) {
				return;
			}
			t->cancelled = ETIMEDOUT;
			iom->cancelEvent(fd, aboo::IOManager::WRITE);
		}, winfo);
	}

	int rt = iom->addEvent(fd, aboo::IOManager::WRITE);
	if (rt == 0) {
		aboo::Fiber::YieldToHold();
		if (timer) {
			timer->cancel();
		}
		if (tinfo->cancelled) {
			errno = tinfo->cancelled;
			return -1;
		}
	} else {
		if (timer) {
			timer->cancel();
		}
		ABOO_LOG_ERROR(g_logger) << "connect addEvent(" << fd << ", WRITE) error";
	}

	int error = 0;
	socklen_t len = sizeof(int);
	if (-1 == getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, &len)) {
		return -1;
	}
	if (!error) {
		return 0;
	} else {
		errno = error;
		return -1;
	}
}

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	return connect_wait_timeout(sockfd, addr, addrlen, aboo::s_connect_timeout);
}

int accept(int s, struct sockaddr* addr, socklen_t* addrlen) {
	int fd = do_io(s, accept_f, "accept", aboo::IOManager::READ, SO_RCVTIMEO, addr, addrlen);
	if (fd >= 0) {
		aboo::FdMgr::getInstance()->get(fd, true);
	}
	return fd;
}

ssize_t read(int fd, void *buf, size_t count) {
	return do_io(fd, read_f, "read", aboo::IOManager::READ, SO_RCVTIMEO, buf, count);
}

ssize_t readv(int fd, const struct iovec *iov, int iovcnt) {
	return do_io(fd, readv_f, "readv", aboo::IOManager::READ, SO_RCVTIMEO, iov, iovcnt);
}

ssize_t recv(int sockfd, void *buf, size_t len, int flags) {
	return do_io(sockfd, recv_f, "recv", aboo::IOManager::READ, SO_RCVTIMEO, buf, len, flags);
}

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) {
	return do_io(sockfd, recvfrom_f, "recvfrom", aboo::IOManager::READ, SO_RCVTIMEO, buf, len, flags, src_addr, addrlen);
}

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags) {
	return do_io(sockfd, recvmsg_f, "recvmsg", aboo::IOManager::READ, SO_RCVTIMEO, msg, flags);
}

ssize_t write(int fd, const void *buf, size_t count) {
	return do_io(fd, write_f, "write", aboo::IOManager::WRITE, SO_SNDTIMEO, buf, count);
}

ssize_t writev(int fd, const struct iovec *iov, int iovcnt) {
	return do_io(fd, writev_f, "writev", aboo::IOManager::WRITE, SO_SNDTIMEO, iov, iovcnt);
}

ssize_t send(int sockfd, const void *buf, size_t len, int flags) {
	return do_io(sockfd, send_f, "send", aboo::IOManager::WRITE, SO_SNDTIMEO, buf, len, flags);
}

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen) {
	return do_io(sockfd, sendto_f, "sendto", aboo::IOManager::WRITE, SO_SNDTIMEO, buf, len, flags, dest_addr, addrlen);
}

ssize_t sendmsg(int sockfd, const struct msghdr *buf, int flags) {
	return do_io(sockfd, sendmsg_f, "sendtomsg", aboo::IOManager::WRITE, SO_SNDTIMEO, buf, flags);
}

int close(int fd) {
	if (!aboo::t_hook_enable) {
		return close_f(fd);
	}

	aboo::FdCtx::ptr ctx = aboo::FdMgr::getInstance()->get(fd);
	if (ctx) {
		auto iom = aboo::IOManager::GetThis();
		if (iom) {
			iom->cancelAll(fd);
		}
		aboo::FdMgr::getInstance()->del(fd);
	}
	return close_f(fd);
}

int fcntl(int fd, int cmd, .../* arg */) {
	va_list va;
	va_start(va, cmd);
	switch(cmd) {
		case F_SETFL:
			{
				int arg = va_arg(va, int);
				va_end(va);
				aboo::FdCtx::ptr ctx = aboo::FdMgr::getInstance()->get(fd);
				if (!ctx || ctx->isClosed() || !ctx->isSocket()) {
					return fcntl_f(fd, cmd, arg);
				}
				ctx->setUserNonblock(arg & O_NONBLOCK);
				if (ctx->getSysNonblock()) {
					arg |= O_NONBLOCK;
				} else {
					arg &= ~O_NONBLOCK;
				}
				return fcntl_f(fd, cmd, arg);
			}
			break;
		case F_GETFL:
			{
				va_end(va);
				int arg = fcntl_f(fd, cmd);
				aboo::FdCtx::ptr ctx = aboo::FdMgr::getInstance()->get(fd);
				if (!ctx || ctx->isClosed() || !ctx->isSocket()) {
					return arg;
				}
				if (ctx->getUserNonblock()) {
					return arg | O_NONBLOCK;
				} else {
					return arg & ~O_NONBLOCK;
				}
			}
			break;
		case F_DUPFD:
		case F_DUPFD_CLOEXEC:
		case F_SETFD:
		case F_SETOWN:
		case F_SETSIG:
		case F_SETLEASE:
		case F_NOTIFY:
		case F_SETPIPE_SZ:
			{
				int arg = va_arg(va, int);
				va_end(va);
				return fcntl_f(fd, cmd, arg);
			}
			break;
		case F_GETFD:
		case F_GETOWN:
		case F_GETSIG:
		case F_GETLEASE:
		case F_GETPIPE_SZ:
			{
				va_end(va);
				return fcntl_f(fd, cmd);
			}
			break;
		case F_SETLK:
		case F_SETLKW:
		case F_GETLK:
			{
				struct flock* arg = va_arg(va, struct flock*);
				va_end(va);
				return fcntl_f(fd, cmd, arg);
			}
			break;
		case F_GETOWN_EX:
		case F_SETOWN_EX:
			{
				struct f_owner_exlock* arg = va_arg(va, struct f_owner_exlock*);
				va_end(va);
				return fcntl_f(fd, cmd, arg);
			}
			break;
		default:
			va_end(va);
			return fcntl_f(fd, cmd);
	}
}

int ioctl(int fd, unsigned long int request, ...) {
	va_list va;
	va_start(va, request);
	void* arg = va_arg(va, void*);
	va_end(va);

	if (FIONBIO == request) {
		bool user_nonblock = !!*(int*)arg;
		aboo::FdCtx::ptr ctx = aboo::FdMgr::getInstance()->get(fd);
		if (!ctx || ctx->isClosed() || !ctx->isSocket()) {
			return ioctl_f(fd, request, arg);
		}
		ctx->setUserNonblock(user_nonblock);
	}
	return ioctl_f(fd, request, arg);
}

int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen) {
	return getsockopt_f(sockfd, level, optname, optval, optlen);
}

int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) {
	if (!aboo::t_hook_enable) {
		return setsockopt_f(sockfd, level, optname, optval, optlen);
	}
	if (level == SOL_SOCKET) {
		if (optname == SO_RCVTIMEO || optname == SO_SNDTIMEO) {
			aboo::FdCtx::ptr ctx = aboo::FdMgr::getInstance()->get(sockfd);
			if (ctx) {
				const timeval* tv = (const timeval*)optval;
				ctx->setTimeout(optname, tv->tv_sec * 1000 + tv->tv_usec / 1000);
			}
		}
	}
	return setsockopt_f(sockfd, level, optname, optval, optlen);
}

}
