#include "../aboo/http/http_server.h"
#include "../aboo/log.h"


aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

void run() {
	aboo::Address::ptr addr = aboo::Address::LookupAnyIPAddress("0.0.0.0:8020");
	if (!addr) {
		ABOO_LOG_ERROR(g_logger) << "get address error";
		return;
	}
	aboo::http::HttpServer::ptr http_server(new aboo::http::HttpServer(true));
	while (!http_server->bind(addr)) {
		ABOO_LOG_ERROR(g_logger) << "bind " << *addr << " fail";
		sleep(1);
	}

	http_server->start();
}

int main(int argc, char** argv) {
	aboo::IOManager iom(1);
	iom.schedule(run);
	return 0;
}
