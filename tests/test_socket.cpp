#include "../aboo/socket.h"
#include "../aboo/aboo.h"
#include "../aboo/iomanager.h"

static aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

void test_socket() {
	aboo::IPAddress::ptr addr = aboo::Address::LookupAnyIPAddress("www.baidu.com");
	if (addr) {
		ABOO_LOG_INFO(g_logger) << "get address: " << addr->toString();
	} else {
		ABOO_LOG_ERROR(g_logger) << "get address failure";
		return;
	}

	aboo::Socket::ptr sock = aboo::Socket::CreateTCP(addr);
	addr->setPort(80);
	ABOO_LOG_INFO(g_logger) << "address=" << addr->toString();
	if (!sock->connect(addr)) {
		ABOO_LOG_ERROR(g_logger) << "connect " << addr->toString() << " failure";
		return;
	} else {
		ABOO_LOG_INFO(g_logger) << "connect " << addr->toString() << " connected";
	}

	const char buff[] = "GET / HTTP/1.0\r\n\r\n";
	int ret = sock->send(buff, sizeof(buff));
	if (ret <= 0) {
		ABOO_LOG_ERROR(g_logger) << "send fail ret=" << ret;
		return;
	}

	std::string buffs;
	buffs.resize(4096);
	ret = sock->recv(&buffs[0], buffs.size());

	if (ret <= 0) {
		ABOO_LOG_ERROR(g_logger) << "recv fail ret=" << ret;
		return;
	}

	buffs.resize(ret);
	ABOO_LOG_INFO(g_logger) << buffs;
}

int main(int argc, char** argv) {
	aboo::IOManager iom;
	iom.schedule(&test_socket);
	return 0;
}
