#ifndef __ABOO_LOG_H__
#define __ABOO_LOG_H__

#include <string>
#include <stdint.h>
#include <iostream>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include "util.h"
#include "singleton.h"
#include "thread.h"

#define ABOO_LOG_LEVENT(logger, level) \
	if (logger->getLevel() <= level) \
		aboo::LogEventWrap(aboo::LogEvent::ptr(new aboo::LogEvent(logger, level, __FILE__, __LINE__, 0, aboo::getThreadId(), aboo::getFiberId(), time(0), aboo::Thread::GetName()))).getSS()

#define ABOO_LOG_DEBUG(logger) ABOO_LOG_LEVENT(logger, aboo::LogLevel::DEBUG)
#define ABOO_LOG_INFO(logger) ABOO_LOG_LEVENT(logger, aboo::LogLevel::INFO)
#define ABOO_LOG_WARN(logger) ABOO_LOG_LEVENT(logger, aboo::LogLevel::WARN)
#define ABOO_LOG_ERROR(logger) ABOO_LOG_LEVENT(logger, aboo::LogLevel::ERROR)
#define ABOO_LOG_FATAL(logger) ABOO_LOG_LEVENT(logger, aboo::LogLevel::FATAL)

#define ABOO_LOG_FMT_LEVEL(logger, level, fmt, ...) \
	if (logger->getLevel() <= level) \
		aboo::LogEventWrap(aboo::LogEvent::ptr(new aboo::LogEvent(logger, level, __FILE__, __LINE__, 0, aboo::getThreadId(), aboo::getFiberId(), time(0), aboo::Thread::GetName()))).getEvent()->format(fmt, __VA_ARGS__)

#define ABOO_LOG_FMT_DEBUG(logger, fmt, ...) ABOO_LOG_FMT_LEVEL(logger, aboo::LogLevel::DEBUG, fmt, __VA_ARGS__)
#define ABOO_LOG_FMT_INFO(logger, fmt, ...) ABOO_LOG_FMT_LEVEL(logger, aboo::LogLevel::INFO, fmt, __VA_ARGS__)
#define ABOO_LOG_FMT_WARN(logger, fmt, ...) ABOO_LOG_FMT_LEVEL(logger, aboo::LogLevel::WARN, fmt, __VA_ARGS__)
#define ABOO_LOG_FMT_ERROR(logger, fmt, ...) ABOO_LOG_FMT_LEVEL(logger, aboo::LogLevel::ERROR, fmt, __VA_ARGS__)
#define ABOO_LOG_FMT_FATAL(logger, fmt, ...) ABOO_LOG_FMT_LEVEL(logger, aboo::LogLevel::FATAL, fmt, __VA_ARGS__)

#define ABOO_LOG_ROOT() aboo::LoggerMgr::getInstance()->getRoot()
#define ABOO_LOG_NAME(name) aboo::LoggerMgr::getInstance()->getLogger(name)

namespace aboo {

class Logger;
class LoggerManager;

// 日志级别
class LogLevel{
public:
	enum Level {
		UNKNOW = 0,
		DEBUG = 1,
		INFO = 2,
		WARN = 3,
		ERROR = 4,
		FATAL = 5
	};

	static const char* ToString(LogLevel::Level level);
	static LogLevel::Level FromString(const std::string& str);
};

// 日志事件
class LogEvent {
public:
	typedef std::shared_ptr<LogEvent> ptr;
	LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, int32_t m_line, uint32_t elapse, uint32_t thread_id, uint32_t fiber_id, uint64_t time, const std::string& thread_name);
	const char* getFile() const { return m_file; }
	int32_t getLine() const { return m_line; }
	uint32_t getElapse() const { return m_elapse; }
	uint32_t getThreadId() const { return m_threadId; }
	uint32_t getFiberId() const { return m_fiberId; }
	uint64_t getTime() const { return m_time; }
	const std::string& getThreadName() const { return m_threadName; }
	std::string getContent() const { return m_ss.str(); }
	std::shared_ptr<Logger> getLogger() const { return m_logger; }
	LogLevel::Level getLevel() const { return m_level; }

	std::stringstream& getSS() { return m_ss; }
	void format(const char *format, ...);
	void format(const char *format, va_list al);
private:
	const char* m_file = nullptr;	//文件名
	int32_t m_line = 0;		//行号
	uint32_t m_elapse = 0;		//程序启动开始到现在的毫秒数
	uint32_t m_threadId = 0;	//线程ID
	uint32_t m_fiberId = 0;		//协程ID
	uint64_t m_time = 0;		//时间戳
	std::string m_threadName;
	std::stringstream m_ss;
	std::shared_ptr<Logger> m_logger;
	LogLevel::Level m_level;
};

class LogEventWrap {
public:
	LogEventWrap(LogEvent::ptr e);
	~LogEventWrap();

	std::stringstream& getSS() { return m_event->getSS(); }
	LogEvent::ptr getEvent() { return m_event; }
private:
	LogEvent::ptr m_event;
};

// 日志格式器
class LogFormatter {
public:
	typedef std::shared_ptr<LogFormatter> ptr;
	LogFormatter(const std::string& pattern);

	void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
	class FormatItem {
	public:
		typedef std::shared_ptr<FormatItem> ptr;
		virtual ~FormatItem() { }
		virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
	};
	void init();

	bool isError() const { return m_error; }
	void setPattern(const std::string& str) { 
		std::cout << "\n\n////////////////" << str << "\\\\\\\\\n\n";
		m_pattern = str;
		std::cout << "\n\n\\\\\\\\\\\\\\" << str << "///////////\n\n";
	}
	const std::string getPattern() { return m_pattern; }
private:
	std::string m_pattern;
	std::vector<FormatItem::ptr> m_items;
	bool m_error = false;
};

// 日志目标输出
class LogAppender {
friend class Logger;
public:
	typedef std::shared_ptr<LogAppender> ptr;
	typedef Spinlock MutexType;
	virtual ~LogAppender() { }
	virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;

	virtual std::string toYamlString() = 0;

	void setFormatter(LogFormatter::ptr val);
	LogFormatter::ptr getFormatter();

	LogLevel::Level getLevel() const { return m_level; }
	void setLevel(LogLevel::Level val) { m_level = val; }
protected:
	LogLevel::Level m_level;
	bool m_hasFormatter = false;
	MutexType m_mutex;
	LogFormatter::ptr m_formatter;
};

// 日志器
class Logger : public std::enable_shared_from_this<Logger> {
friend class LoggerManager;
public:
	typedef std::shared_ptr<Logger> ptr;
	typedef Spinlock MutexType;

	Logger(const std::string& name = "root");
	void log(LogLevel::Level level, LogEvent::ptr event);

	void debug(LogEvent::ptr event);
	void info(LogEvent::ptr event);
	void warn(LogEvent::ptr event);
	void error(LogEvent::ptr event);
	void fatal(LogEvent::ptr event);

	void addAppender(LogAppender::ptr appender);
	void delAppender(LogAppender::ptr appender);
	void clearAppenders();
	const std::string& getName() const { return m_name; }
	LogFormatter::ptr getFormatter();
	LogLevel::Level getLevel() const { return m_level; }
	void setLevel(LogLevel::Level val) { m_level = val; }
	void setFormatter(LogFormatter::ptr val);
	void setFormatter(std::string val);

	std::string toYamlString();
private:
	MutexType m_mutex;
	std::string m_name;			//日志名称
	LogLevel::Level m_level;		//日志级别
	std::list<LogAppender::ptr> m_appenders;//Appender集合
	LogFormatter::ptr m_formatter;
	Logger::ptr m_root;
};

class StdoutLogAppender : public LogAppender {
public:
	typedef std::shared_ptr<StdoutLogAppender> ptr;
	void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
	std::string toYamlString() override;
};

class FileLogAppender : public LogAppender {
public:
	typedef std::shared_ptr<FileLogAppender> ptr;
	void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
	std::string toYamlString() override;
	FileLogAppender(const std::string &filename);
	FileLogAppender() = default;
	bool reopen();
private:
	std::string m_filename;
	std::ofstream m_filestream;
	uint64_t m_lastTime = 0;
};

class LoggerManager {
public:
	typedef Spinlock MutexType;
	LoggerManager();
	Logger::ptr getLogger(const std::string& name);

	void init();
	Logger::ptr getRoot() const { return m_root; }

	std::string toYamlString();
private:
	MutexType m_mutex;
	std::map<std::string, Logger::ptr> m_loggers;
	Logger::ptr m_root;
};

typedef aboo::Singleton<LoggerManager> LoggerMgr;

}
#endif
