#include <iostream>
#include "../aboo/http/http_connection.h"
#include "../aboo/log.h"
#include "../aboo/iomanager.h"

static aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

void test_pool() {
	aboo::http::HttpConnectionPool::ptr pool(new aboo::http::HttpConnectionPool("www.sylar.top", "", 80, 10, 1000 * 30, 5));
	aboo::IOManager::GetThis()->addTimer(1000, [pool](){
		auto r = pool->doGet("/", 300);
		ABOO_LOG_INFO(g_logger) << r->toString();
	}, true);
}

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

	ABOO_LOG_INFO(g_logger) << "=======================================================";

	auto r = aboo::http::HttpConnection::DoGet("http://www.sylar.top/blog/", 300);
	ABOO_LOG_INFO(g_logger) << "result=" << r->result
		<< " error=" << r->error
		<< " rsp=" << (r->response ? r->response->toString() : "");

	ABOO_LOG_INFO(g_logger) << "=======================================================";
	test_pool();
}

int main(int argc, char** argv) {
	aboo::IOManager iom(2);
	iom.schedule(run);
	return 0;
}
