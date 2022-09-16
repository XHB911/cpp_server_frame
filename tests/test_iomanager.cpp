#include "../aboo/aboo.h"
#include "../aboo/iomanager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

int sock = 0;

void test_fiber() {
	ABOO_LOG_INFO(g_logger) << "test_fiber sock=" << sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(sock, F_SETFL, O_NONBLOCK);

	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	inet_pton(AF_INET, "110.242.68.4", &addr.sin_addr.s_addr);

	if (!connect(sock, (const sockaddr*)&addr, sizeof(addr))) {
	} else if (errno == EINPROGRESS) {
		ABOO_LOG_INFO(g_logger) << "add event errno=" << errno << " " << strerror(errno);
		aboo::IOManager::GetThis()->addEvent(sock, aboo::IOManager::READ, [](){
			ABOO_LOG_INFO(g_logger) << "read callback";
		});
		aboo::IOManager::GetThis()->addEvent(sock, aboo::IOManager::WRITE, [](){
			ABOO_LOG_INFO(g_logger) << "write callback";
			aboo::IOManager::GetThis()->cancelEvent(sock, aboo::IOManager::READ);
			close(sock);
		});
	} else {
		ABOO_LOG_INFO(g_logger) << "else " << errno << " " << strerror(errno);
	}
}

void test1() {
	aboo::IOManager iom(2, false);
	iom.schedule(&test_fiber);
}

void test_timer() {
	aboo::IOManager iom(2);
	aboo::Timer::ptr timer = iom.addTimer(1000, [&timer](){
		static int i = 0;
		ABOO_LOG_INFO(g_logger) << "hello timer i=" << i;
		if (++i == 3) {
			timer->cancel();
		}
	}, true);
}

int main(int argc, char** argv) {
	test_timer();
	return 0;
}
