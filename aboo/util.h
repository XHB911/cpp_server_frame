#ifndef __ABOO_UTIL_H__
#define __ABOO_UTIL_H__

#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdint.h>
#include <vector>
#include <string>

namespace aboo {

pid_t getThreadId();
uint32_t getFiberId();

void Backtrace(std::vector<std::string>& bt, int size = 64, int skip = 1);
std::string BacktraceToString(int size = 64, int skip = 2, const std::string& prefix = "");

// 时间ms/us
uint64_t GetCurrentMS();
uint64_t GetCurrentUS();

}

#endif
