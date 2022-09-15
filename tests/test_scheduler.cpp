#include "../aboo/aboo.h"

aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

void test_fiber() {
	ABOO_LOG_INFO(g_logger) << "test in fiber";
	static int s_count = 5;
	sleep(1);
	if (--s_count >= 0) {
		aboo::Scheduler::GetThis()->schedule(&test_fiber, aboo::getThreadId());
	}
}

int main(int argc, char** argv) {
	ABOO_LOG_INFO(g_logger) << "begin";
	aboo::Scheduler sc(3, true, "test");
	sc.start();
	ABOO_LOG_INFO(g_logger) << "sechedule";
	sc.schedule(&test_fiber);
	sc.stop();
	ABOO_LOG_INFO(g_logger) << "over";
	return 0;
}
