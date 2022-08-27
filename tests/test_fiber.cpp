#include "../aboo/aboo.h"

aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

void run_in_fiber() {
	ABOO_LOG_INFO(g_logger) << "run_in_fiber begin";
	//aboo::Fiber::GetThis()->swapOut();
	aboo::Fiber::YieldToHold();
	ABOO_LOG_INFO(g_logger) << "run_in_fiber end";
	aboo::Fiber::YieldToHold();
}

void test_fiber() {
	ABOO_LOG_INFO(g_logger) << "main begin -1";
	{
		aboo::Fiber::GetThis();
		ABOO_LOG_INFO(g_logger) << "main begin";
		aboo::Fiber::ptr fiber(new aboo::Fiber(run_in_fiber));
		fiber->swapIn();
		ABOO_LOG_INFO(g_logger) << "main after swapIn";
		fiber->swapIn();
		ABOO_LOG_INFO(g_logger) << "main after end";
		fiber->swapIn();
	}
	ABOO_LOG_INFO(g_logger) << "main after end2";
}

int main(int argc, char** argv) {
	aboo::Thread::SetName("main");

	std::vector<aboo::Thread::ptr> thrs;
	for (int i = 0; i < 3; i++) {
		thrs.push_back(aboo::Thread::ptr(new aboo::Thread(&test_fiber, "nam_" + std::to_string(i))));
	}
	for (auto i : thrs) i->join();
	return 0;
}
