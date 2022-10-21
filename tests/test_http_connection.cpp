#include <iostream>
#include "../aboo/http/http_connection.h"
#include "../aboo/log.h"
#include "../aboo/iomanager.h"

static aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

void run() {
	aboo::Address::ptr addr = aboo::Address::LookupAnyIPAddress("www.sylar.top:80");
	if (!addr) {
		ABOO_LOG_ERROR(g_logger) << "get addr error";
		return;
	}
	aboo::Socket::ptr sock = aboo::Socket::CreateTCP(addr);
	bool rt = sock->connect(addr);
	if (!rt) {
		ABOO_LOG_ERROR(g_logger) << "connect " << *addr <<" failed";
		return;
	}

	aboo::http::HttpConnection::ptr conn(new aboo::http::HttpConnection(sock));
	aboo::http::HttpRequest::ptr req(new aboo::http::HttpRequest);
	req->setPath("/blog/");
	req->setHeader("host", "www.sylar.top");
	ABOO_LOG_INFO(g_logger) << "req:" << std::endl
		<< *req;

	conn->sendRequest(req);
	auto rsp = conn->recvResponse();

	if (!rsp) {
		ABOO_LOG_ERROR(g_logger) << "recv response error";
		return;
	}
	ABOO_LOG_INFO(g_logger) << "rsp:" << std::endl
		<< *rsp;
}

int main(int argc, char** argv) {
	aboo::IOManager iom(2);
	iom.schedule(run);
	return 0;
}
