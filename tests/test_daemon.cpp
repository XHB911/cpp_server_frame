#include "../aboo/daemon.h"
#include "../aboo/iomanager.h"
#include "../aboo/log.h"

static aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

aboo::Timer::ptr timer;
int server_main(int argc, char** argv) {
	ABOO_LOG_INFO(g_logger) << aboo::ProcessInfoMgr::getInstance()->toString();
	aboo::IOManager iom(1);
	timer = iom.addTimer(1000, [](){
		ABOO_LOG_INFO(g_logger) << "onTimer";
		static int count = 0;
		if (++count > 10) {
			timer->cancel();
		}
	}, true);
	return 0;
}

int main(int argc, char** argv) {
	return aboo::start_daemon(argc, argv, server_main, argc != 1);
}
