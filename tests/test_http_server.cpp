#include "../aboo/http/http_server.h"
#include "../aboo/log.h"

static aboo::Logger::ptr g_logger = ABOO_LOG_ROOT();

void run() {
	aboo::http::HttpServer::ptr server(new aboo::http::HttpServer);
	aboo::Address::ptr addr = aboo::Address::LookupAnyIPAddress("0.0.0.0:8020");
	while (!server->bind(addr)) {
		sleep(2);
	}
	auto sd = server->getServletDispath();
	sd->addServlet("/aboo/xx", [](aboo::http::HttpRequest::ptr req, aboo::http::HttpResponse::ptr rsp, aboo::http::HttpSession::ptr session){
		rsp->setBody(req->toString());
		return 0;
	});
	server->start();

	sd->addGlobServlet("/aboo/*", [](aboo::http::HttpRequest::ptr req, aboo::http::HttpResponse::ptr rsp, aboo::http::HttpSession::ptr session){
		rsp->setBody("Glob:\r\n" + req->toString());
		return 0;
	});
	server->start();
}

int main(int argc, char** argv) {
	aboo::IOManager iom(2);
	iom.schedule(run);
	return 0;
}
