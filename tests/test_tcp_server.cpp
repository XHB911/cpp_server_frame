#include "../aboo/tcp_server.h"
#include "../aboo/iomanager.h"
#include "../aboo/log.h"

static aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

void run() {
	auto addr = aboo::Address::LookupAny("0.0.0.0:8030");
	//auto addr2 = aboo::UnixAddress::ptr(new aboo::UnixAddress("/tmp/unix_addr"));
	std::vector<aboo::Address::ptr> addrs;
	addrs.push_back(addr);
	//addrs.push_back(addr2);

	aboo::TcpServer::ptr tcp_server(new aboo::TcpServer);
	std::vector<aboo::Address::ptr> fails;
	while (!tcp_server->bind(addrs, fails)) {
		sleep(2);
	}
	tcp_server->start();
	ABOO_LOG_INFO(g_logger) << "start over";
}

int main(int argc, char** argv) {
	aboo::IOManager iom(2);
	iom.schedule(run);
	return 0;
}
