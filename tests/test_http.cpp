#include "../aboo/http/http.h"
#include "../aboo/log.h"

void test_request() {
	aboo::http::HttpRequest::ptr req(new aboo::http::HttpRequest);
	req->setHeader("host", "www.sylar.top");
	req->setBody("hello sylar");

	req->dump(std::cout) << std::endl;
}

void test_response() {
	aboo::http::HttpResponse::ptr rsp(new aboo::http::HttpResponse);
	rsp->setHeader("X-X", "aboo");
	rsp->setStatus((aboo::http::HttpStatus)400);
	rsp->setClose(false);
	rsp->setBody("hello aboo");

	rsp->dump(std::cout <<std::endl);
}

int main(int argc, char** argv) {
	test_request();
	test_response();
	return 0;
}
