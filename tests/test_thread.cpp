#include "../aboo/aboo.h"
#include <unistd.h>

aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

//aboo::RWMutex s_mutex;
aboo::Mutex s_mutex;

int count = 0;

void fun1() {
	ABOO_LOG_INFO(g_logger) << "thread_id" << aboo::Thread::GetName() << " this.name: " << aboo::Thread::GetThis()->getName() << " id: " << aboo::getThreadId() << " this.id: " << aboo::Thread::GetThis()->getId();
	for (int i = 0; i < 100000; i++) {
		//aboo::RWMutex::WriteLock lock(s_mutex);
		aboo::Mutex::Lock lock(s_mutex);
		count += 1;
	}
}

void fun2() {
	for (int i = 0; i < 10000; i++) {
		ABOO_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	}
}

void fun3() {
	for (int i = 0; i < 10000; i++) {
		ABOO_LOG_INFO(g_logger) << "========================================================";
	}
}

int main(int argc, char** argv) {
	ABOO_LOG_INFO(g_logger) << "thread test begin";
	YAML::Node root = YAML::LoadFile("/home/hb/cpp_server_frame/bin/conf/log2.yml");
	aboo::Config::LoadFromYaml(root);

	std::vector<aboo::Thread::ptr> thrs;
	for (int i = 0; i < 2; i++) {
		aboo::Thread::ptr thr(new aboo::Thread(&fun2, "name_" + std::to_string(2 * i)));
		aboo::Thread::ptr thr2(new aboo::Thread(&fun3, "name_" + std::to_string(2 * i + 1)));
		thrs.push_back(thr);
		thrs.push_back(thr2);
	}

	for (size_t i = 0; i < thrs.size(); i++) {
		thrs[i]->join();
	}

	ABOO_LOG_INFO(g_logger) << "thread test end";
	ABOO_LOG_INFO(g_logger) << "count=" << count;

	return 0;
}
