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

void Backtrace(std::vector<std::string>& bt, int size, int skip = 1);
std::string BacktraceToString(int size, int skip = 2, const std::string& prefix = "");

}

#endif
