#include <iostream>
#include "../aboo/log.h"
#include "../aboo/util.h"

int main(int argc, char** argv) {
	aboo::Logger::ptr logger(new aboo::Logger);
	logger->addAppender(aboo::LogAppender::ptr(new aboo::StdoutLogAppender));

	aboo::FileLogAppender::ptr file_appender(new aboo::FileLogAppender("./log.txt"));

	aboo::LogFormatter::ptr fmt(new aboo::LogFormatter("%d%T%p%T%m%n"));
	file_appender->setFormatter(fmt);
	file_appender->setLevel(aboo::LogLevel::ERROR);

	logger->addAppender(file_appender);

	//aboo::LogEvent::ptr event(new aboo::LogEvent(__FILE__, __LINE__, 0, aboo::getThreadId(), aboo::getFiberId(), time(0)));

	//logger->log(aboo::LogLevel::DEBUG, event);

	ABOO_LOG_INFO(logger) << "test macro info";
	ABOO_LOG_ERROR(logger) << "test macro error";

	ABOO_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

	auto l = aboo::LoggerMgr::getInstance()->getLogger("xx");
	ABOO_LOG_INFO(l) << "xxx";

	std::cout << "Hello aboo Log" << std::endl;
	return 0;
}
