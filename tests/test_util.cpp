#include "../aboo/aboo.h"
#include <assert.h>

aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

void test_assert() {
	ABOO_LOG_INFO(g_logger) << aboo::BacktraceToString(10, 0, "    ");
	ABOO_ASSERT2(0 == 1, "abcdef xx");
}

int main(int argc, char **argv) {
	test_assert();
	return 0;
}
