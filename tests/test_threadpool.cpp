#include "../aboo/threadpool.h"
#include "../aboo/log.h"

#include <unistd.h>
#include <iostream>

aboo::Logger::ptr g_logger = ABOO_LOG_NAME("user");

void fun1() {
	int i = 0;
	while (i <= 1000) ++i;
	ABOO_LOG_INFO(g_logger) << "fun1: " << i;
}

int fun2(int x, int y) {
	int z = x + y;
	sleep(1);
	return z;
}

int main() {
	aboo::ThreadPool pool;
	pool.setMode(aboo::ThreadPoolMode::CACHED);
	pool.start(4);
	for (int i = 0; i < 10; ++i) {
		pool.addTask(fun1);
	}
	auto i1 = pool.addTask(fun2, 1, 2);
	auto i2 = pool.addTask(fun2, 2, 3);
	auto i3 = pool.addTask(fun2, 3, 4);
	auto i4 = pool.addTask(fun2, 4, 5);
	auto i5 = pool.addTask(fun2, 5, 6);
	std::getchar();
	std::cout << i1.get() << std::endl;
	std::cout << i2.get() << std::endl;
	std::cout << i3.get() << std::endl;
	std::cout << i4.get() << std::endl;
	std::cout << i5.get() << std::endl;
	return 0;
}
