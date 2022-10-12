#include "../aboo/http/http_parser.h"
#include "../aboo/log.h"

static aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

const char test_request_data[] = "GET / HTTP/1.1\r\n"
	"Host: www.sylar.top\r\n"
	"Content-Length: 10\r\n\r\n"
	"1234567890";

void test_request() {
	aboo::http::HttpRequestParser parser;
	std::string tmp = test_request_data;
	size_t s = parser.execute(&tmp[0], tmp.size());
	ABOO_LOG_INFO(g_logger) << "execute rt=" << s
		<< "has_error=" << parser.hasError()
		<< " is_finished=" << parser.isFinished()
		<< " total=" << tmp.size()
		<< " content-length=" << parser.getContentLength();
	tmp.resize(tmp.size() - s);
	ABOO_LOG_INFO(g_logger) << parser.getData()->toString();
	ABOO_LOG_INFO(g_logger) << tmp;
}

const char test_response_data[] = "HTTP/1.1 200 OK\r\n"
		"Accept-Ranges: bytes\r\n"
		"Cache-Control: no-Cache\r\n"
		"Connection: keep-alive\r\n"
		"Content-Length: 9508\r\n"
		"Content-Type: text/html\r\n"
		"Date: Wed, 12 Oct 2022 13:41:50 GMT\r\n"
		"Pragma: no-cache\r\n"
		"Server: BWS/1.1\r\n\r\n"
		"<html>\r\n"
		"<meta http-equiv=\"refresh\" content=\"0;url=http://www.baidu.com/\">\r\n"
		"</html>\r\n";

void test_response() {
	aboo::http::HttpResponseParser parser;
	std::string tmp = test_response_data;
	size_t s = parser.execute(&tmp[0], tmp.size());
	ABOO_LOG_ERROR(g_logger) << "execute rt=" << s
		<< " has_error=" << parser.hasError()
		<< " is_finish=" << parser.isFinished()
		<< " total=" << tmp.size()
		<< " content-length=" << parser.getContentLength();
	tmp.resize(tmp.size() - s);
	ABOO_LOG_INFO(g_logger) << parser.getData()->toString();
	ABOO_LOG_INFO(g_logger) << tmp;
}

int main(int argc, char** argv) {
	test_request();
	ABOO_LOG_INFO(g_logger) << "--------------------------";
	test_response();
	return 0;
}
