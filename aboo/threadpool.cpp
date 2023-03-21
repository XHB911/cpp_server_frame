#include <chrono>

#include "threadpool.h"
#include "log.h"
#include "config.h"

namespace aboo {

// 任务的阙值
static ConfigVar<uint32_t>::ptr TASK_MAX_THRESHOLD = Config::Lookup<uint32_t>("threadpool.task.threshold", 1024, "threadpool's task max threshold.");
// 线程数量的阙值
static ConfigVar<uint32_t>::ptr THREAD_MAX_THRESHOLD = Config::Lookup<uint32_t>("threadpool.thread.threshold", 64, "threadpool's thread num max threshold.");
// 线程的最大空闲时间
static ConfigVar<uint32_t>::ptr THREAD_MAX_IDLE_TIME = Config::Lookup<uint32_t>("threadpool.thread.idlemaxtime", 60, "threadpool's thread max idle time(s).");

ThreadPool::ThreadPool() :
		m_threads_limit_num(THREAD_MAX_THRESHOLD->getValue()),
		m_thread_init_num(0),
		m_threads_idle_num(0),
		m_threads_cur_num(0),
		m_tasks_limit_num(TASK_MAX_THRESHOLD->getValue()),
		m_tasks_cur_num(0),
		m_mode(ThreadPoolMode::FIXED),
		m_state(false) {  }

ThreadPool::~ThreadPool() {
	// 设置结束状态，加锁处理，通知所有进程把任务处理完毕，阻塞在结束条件变量处
	m_state = false;
	std::unique_lock<std::mutex> lock(m_mutex);
	m_con_task_noempty.notify_all();
	m_con_end.wait(lock, [&]()->bool { return m_thread_map.size() == 0; });
}

void ThreadPool::start(size_t num) {
	// 设置开始状态，初始化线程数量以及线程
	m_state = true;
	m_thread_init_num = num;

	for (size_t i = 0; i < m_thread_init_num; ++i) {
		auto ptr = std::make_unique<Thread>(std::bind(&ThreadPool::thread_func, this), "PoolThread" + std::to_string(m_threads_cur_num + 1));
		pid_t pid_ = ptr->getId();
		m_thread_map.emplace(pid_, std::move(ptr));
		++ m_threads_idle_num;
		++ m_threads_cur_num;
	}
}

void ThreadPool::thread_func() {
	// 记录上次运行的时间
	auto lastTime = std::chrono::high_resolution_clock().now();

	// 死循环进行任务处理
	while (1) {
		std::function<void()> task;
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			ABOO_LOG_INFO(g_logger) << "tid: " << aboo::getThreadId() << " attempt acquire task...";
			while (m_task_que.size() == 0) {
				if (!isRunning()) {
					m_thread_map.erase(aboo::getThreadId());
					ABOO_LOG_INFO(g_logger) << "tid: " << aboo::getThreadId() << " exit due to threadpool is stop...";
					m_con_end.notify_all();
					return;
				}

				// 如果当前线程池的模式为 CACHED，线程数量大于初始线程数量，
				// 并且线程空闲时间大于 THREAD_MAX_IDLE_TIMEOUT，则销毁线程，否则继续等待任务到来
				// 如果当前线程池的模式为 FIXED，则直接等待线程退出即可
				if (m_mode == ThreadPoolMode::CACHED) {
					if (std::cv_status::timeout == m_con_task_noempty.wait_for(lock, std::chrono::seconds(1))) {
						auto now = std::chrono::high_resolution_clock().now();
						if (std::chrono::duration_cast<std::chrono::seconds>(now - lastTime).count() >= THREAD_MAX_IDLE_TIME->getValue() && m_threads_cur_num > m_thread_init_num) {
							m_thread_map.erase(aboo::getThreadId());
							-- m_threads_idle_num;
							-- m_threads_cur_num;
							ABOO_LOG_INFO(g_logger) << "tid: " << aboo::getThreadId() << " exit due to idle timeout...";
							return;
						}
					}
				} else {
					m_con_task_noempty.wait(lock);
				}
			}
			-- m_threads_idle_num;

			ABOO_LOG_INFO(g_logger) << "tid: " << aboo::getThreadId() << " acquire task success.";

			task = m_task_que.front();
			m_task_que.pop();
			-- m_tasks_cur_num;

			if (m_task_que.size()) m_con_task_noempty.notify_all();
			m_con_task_nofull.notify_all();
		}

		if (task) task();
		++ m_threads_idle_num;
		lastTime = std::chrono::high_resolution_clock().now();
	}
}

}
