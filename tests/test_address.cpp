#include "../aboo/address.h"
#include "../aboo/log.h"

aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

void test() {
	std::vector<aboo::Address::ptr> addrs;

	ABOO_LOG_INFO(g_logger) << "begin";
	bool v = aboo::Address::Lookup(addrs, "www.baidu.com:http");
	ABOO_LOG_INFO(g_logger) << "end";
	if (!v) {
		ABOO_LOG_ERROR(g_logger) << "lookup fail";
		return;
	}

	for (size_t i = 0; i < addrs.size(); ++i) {
		ABOO_LOG_INFO(g_logger) << i << " - " << addrs[i]->toString();
	}
}

void test_iface() {
	std::multimap<std::string, std::pair<aboo::Address::ptr, uint32_t>> results;

	bool v = aboo::Address::GetInterfaceAddresses(results);
	if (!v) {
		ABOO_LOG_ERROR(g_logger) << "GetInterfaceAddress fail";
		return;
	}

	for (auto& i : results) {
		ABOO_LOG_INFO(g_logger) << i.first << " - " << i.second.first->toString() << " - " << i.second.second;
	}
}

void test_ipv4() {
	//auto addr = aboo::IPAddress::Create("www.baidu.com");
	auto addr = aboo::IPAddress::Create("127.0.0.8");
	if (addr) {
		ABOO_LOG_INFO(g_logger) << addr->toString();
	}
}

int main(int argc, char** argv) {
	test();
	test_iface();
	test_ipv4();
	return 0;
}
