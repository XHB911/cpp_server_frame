#ifndef __ABOO_MACRO_H__
#define __ABOO_MACRO_H__

#include <string.h>
#include <assert.h>
#include "util.h"

#if defined __GNUC__ || defined __llvm__
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率成立
#define ABOO_LICKLY(x)		__builtin_expect(!!(x), 1)
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率不成立
#define ABOO_UNLICKLY(x)	__builtin_expect(!!(x), 0)
#else
#define ABOO_LICKLY(x)		(x)
#define ABOO_UNLICKLY(x)	(x)
#endif

// 断言宏封装
#define ABOO_ASSERT(x) \
	if (ABOO_UNLICKLY(!(x))) { \
		ABOO_LOG_ERROR(ABOO_LOG_ROOT()) << "ASSERTION: " << #x << "\nbacktrace:\n" << aboo::BacktraceToString(100, 2, "    "); \
		assert(x); \
	}

// 断言宏封装，打印 w
#define ABOO_ASSERT2(x, w) \
	if (ABOO_UNLICKLY(!(x))) { \
		ABOO_LOG_ERROR(ABOO_LOG_ROOT()) << "ASSERTION: " << #x << "\n" << w << "\nbacktrace:\n" << aboo::BacktraceToString(100, 2, "    "); \
		assert(x); \
	}

#endif
