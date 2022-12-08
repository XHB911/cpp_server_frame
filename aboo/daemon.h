#ifndef __ABOO_DAEMON_H__
#define __ABOO_DAEMON_H__

#include <unistd.h>
#include <functional>
#include "singleton.h"

namespace aboo {

struct ProcessInfo {
	// 父进程id
	pid_t parent_id = 0;
	// 主进程id
	pid_t main_id = 0;
	// 父进程启动时间
	uint64_t parent_start_time = 0;
	// 主进程启动时间
	uint64_t main_start_time = 0;
	// 主进程重启次数
	uint32_t restart_count = 0;

	std::string toString() const;
};

typedef aboo::Singleton<ProcessInfo> ProcessInfoMgr;

int start_daemon(int argc, char** argv
		, std::function<int(int argc, char** argv)> main_cb
		, bool is_daemon);
}
#endif
