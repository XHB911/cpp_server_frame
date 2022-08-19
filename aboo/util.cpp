#include "util.h"

namespace aboo {

pid_t getThreadId() {
	return syscall(SYS_gettid);
}

uint32_t getFiberId() {
	return 0;
}

}
