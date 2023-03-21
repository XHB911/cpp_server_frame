#ifndef __ABOO_THREADPOOL_H__
#define __ABOO_THREADPOOL_H__

#include <vector>
#include <queue>
#include <functional>
#include <atomic>
#include <unordered_map>
#include <condition_variable>
#include <future>

#include "log.h"
#include "thread.h"

namespace aboo {

// 打印日志信息
static aboo::Logger::ptr g_logger = ABOO_LOG_NAME("system");

/**
 * @brief 线程池工作模式
 */
enum class ThreadPoolMode {
	// 固定模式，固定线程数量，不可以增加
	FIXED,
	// 缓存模式，动态的增加线程数量
	CACHED,
};

/**
 * @brief 线程池类，用于保存线程池，防止线程池的多次销毁以及创建，浪费 CPU 时间
 */
class ThreadPool {
public:
	/**
	 * @brief 线程池不可 copy
	 */
	ThreadPool(const ThreadPool& oth) = delete;
	/**
	 * @brief 线程池不可 copy
	 */
	ThreadPool& operator=(const ThreadPool& oth) = delete;

	/**
	 * @brief 线程池构造函数
	 */
	ThreadPool();

	/**
	 * @brief 释放线程池的资源
	 */
	~ThreadPool();

	/**
	 * @brief 启动线程池
	 */
	void start(size_t num = std::thread::hardware_concurrency());

	/**
	 * @brief 利用模板来添加线程任务
	 */
	template<typename Func, typename... Args>
	auto addTask(Func&& func, Args&&... args) -> std::future<decltype(func(args...))> {
		using RType = decltype(func(args...));
		auto task = std::make_shared<std::packaged_task<RType()>>(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
		std::future<RType> result = task->get_future();
		std::unique_lock<std::mutex> lock(m_mutex);
		if (!m_con_task_nofull.wait_for(lock, std::chrono::seconds(1), [&]()->bool { return m_task_que.size() < m_tasks_limit_num; })) {
			ABOO_LOG_ERROR(g_logger) << "task queue is full, add task is failure";
			auto task = std::packaged_task<RType()>([]()->RType { return RType(); });
			return task.get_future();
		}

		m_task_que.emplace([task]() { (*task)(); });
		++ m_tasks_cur_num;

		m_con_task_noempty.notify_all();

		if (m_mode == ThreadPoolMode::CACHED && m_tasks_cur_num > m_threads_idle_num && m_threads_cur_num < m_threads_limit_num) {
			ABOO_LOG_INFO(g_logger) << "too many tasks, creating new thread...";

			auto ptr = std::make_unique<Thread>(std::bind(&ThreadPool::thread_func, this), "threadpool" + std::to_string(m_threads_cur_num + 1));
			pid_t pid_ = ptr->getId();
			m_thread_map.emplace(pid_, std::move(ptr));
			++ m_threads_cur_num;
			++ m_threads_idle_num;
		}

		return result;
	}

	/**
	 * @brief 设置线程的最大数量，只有在 CACHED 模式下才能修改，并且在线程池运行时不可修改
	 */
	void setThreadsLimitNum(size_t num) {
		if (isRunning()) return;
		if (m_mode == ThreadPoolMode::CACHED) {
			m_threads_limit_num = num;
		}
	}

	/**
	 * @brief 设置任务的最大数量，在线程池运行时不可修改
	 */
	void setTasksLimitNum(size_t num) {
		if (isRunning()) return;
		m_tasks_limit_num = num;
	}

	/**
	 * @brief 设置线程池的运行模式，在运行时不可被修改
	 */
	void setMode(ThreadPoolMode mode) {
		if (isRunning()) return;
		m_mode = mode;
	}

private:
	/**
	 * @brief 被构造出线程的默认运行函数，该函数循环从任务队列中取出任务来执行
	*/
	void thread_func();
	/**
	 * @brief 获取线程是否在运行
	 */
	bool isRunning() const {
		return m_state;
	}
private:
	// 线程 ID 映射线程指针 MAP
	std::unordered_map<pid_t, std::unique_ptr<Thread>> m_thread_map;
	// 线程池中所有线程的最大数量
	size_t m_threads_limit_num;
	// 初始线程数量
	size_t m_thread_init_num;
	// 线程池中空闲线程的数量
	std::atomic<size_t> m_threads_idle_num;
	// 线程池中当前的线程数量
	std::atomic<size_t> m_threads_cur_num;

	// 线程池的任务队列
	std::queue<std::function<void()>> m_task_que;
	// 任务队列的数量上限
	size_t m_tasks_limit_num;
	// 当前任务的数量
	std::atomic<size_t> m_tasks_cur_num;

	// 线程池的工作模式
	ThreadPoolMode m_mode;
	// 线程池的互斥锁
	std::mutex m_mutex;
	// 线程池的当前状态, true: 运行态, false: 结束态
	std::atomic<bool> m_state;
	// 通知线程 任务队列不空
	std::condition_variable m_con_task_noempty;
	// 通知线程 任务队列不满
	std::condition_variable m_con_task_nofull;
	// 等待线程资源全部回收
	std::condition_variable m_con_end;
};

}

#endif
