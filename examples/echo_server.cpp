#include "../aboo/tcp_server.h"
#include "../aboo/log.h"
#include "../aboo/bytearray.h"
#include "../aboo/iomanager.h"

static aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

class EchoServer : public aboo::TcpServer {
public:
	EchoServer(int type);
	void handleClient(aboo::Socket::ptr client);
private:
	int m_type = 0;
};

EchoServer::EchoServer(int type)
	: m_type(type) {
}

void EchoServer::handleClient(aboo::Socket::ptr client) {
	ABOO_LOG_INFO(g_logger) << "handleClient " << *client;
	aboo::ByteArray::ptr ba(new aboo::ByteArray);
	while (1) {
		ba->clear();
		std::vector<iovec> iovs;
		ba->getWriteBuffers(iovs, 1024);

		int rt = client->recv(&iovs[0], iovs.size());
		if (rt == 0) {
			ABOO_LOG_INFO(g_logger) << "client close: " << *client;
			break;
		} else if (rt < 0) {
			ABOO_LOG_ERROR(g_logger) << "client error rt=" << rt
				<< " errno=" << errno << " strerr=" << strerror(errno);
			break;
		}
		ba->setPosition(ba->getPosition() + rt);

		ba->setPosition(0);
		if (m_type == 1) { // text
			std::cout << ba->toString();
		} else {
			std::cout << ba->toHexString();
		}
	}
}

int type = 1;

void run() {
	EchoServer::ptr es(new EchoServer(type));
	auto addr = aboo::Address::LookupAny("0.0.0.0:8020");
	while (!es->bind(addr)) {
		sleep(2);
	}
	es->start();
}

int main(int argc, char** argv) {
	if (argc < 2) {
		ABOO_LOG_INFO(g_logger) << "used as[" << argv[0] << " -t] or [" << argv[0] << " -b]";
		return 1;
	}

	if (!strcmp(argv[1], "-b")) {
		type = 2;
	}

	aboo::IOManager iom(2);
	iom.schedule(run);
	return 0;
}
