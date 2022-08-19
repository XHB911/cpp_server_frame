#ifndef __ABOO_UTIL_H__
#define __ABOO_UTIL_H__

#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdint.h>

namespace aboo {

pid_t getThreadId();
uint32_t getFiberId();

}

#endif
