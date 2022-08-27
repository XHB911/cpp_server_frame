#ifndef __ABOO_MACRO_H__
#define __ABOO_MACRO_H__

#include <string.h>
#include <assert.h>
#include "util.h"

#define ABOO_ASSERT(x) \
	if (!(x)) { \
		ABOO_LOG_ERROR(ABOO_LOG_ROOT()) << "ASSERTION: " << #x << "\nbacktrace:\n" << aboo::BacktraceToString(100, 2, "    "); \
		assert(x); \
	}

#define ABOO_ASSERT2(x, w) \
	if (!(x)) { \
		ABOO_LOG_ERROR(ABOO_LOG_ROOT()) << "ASSERTION: " << #x << "\n" << w << "\nbacktrace:\n" << aboo::BacktraceToString(100, 2, "    "); \
		assert(x); \
	}

#endif
