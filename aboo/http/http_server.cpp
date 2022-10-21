#include "http_server.h"
#include "../log.h"

namespace aboo {
namespace http {

static aboo::Logger::ptr g_logger = ABOO_LOG_NAME("system");

HttpServer::HttpServer(bool keepalive, aboo::IOManager* worker, aboo::IOManager* accept_worker)
	: TcpServer(worker, accept_worker)
	, m_isKeepalive(keepalive) {
	m_dispatch.reset(new ServletDispatch);
}

void HttpServer::handleClient(Socket::ptr client) {
	HttpSession::ptr session(new HttpSession(client));
	do {
		auto req = session->recvRequest();
		if (!req) {
			ABOO_LOG_WARN(g_logger) << "recv http request fail, errno=" << errno
				<< " strerr=" << strerror(errno)
				<< " client: " << *client;
			break;
		}

		HttpResponse::ptr rsp(new HttpResponse(req->getVersion(), req->isClose() || !m_isKeepalive));

		m_dispatch->handle(req, rsp, session);

		//rsp->setBody("hello aboo");

		//ABOO_LOG_INFO(g_logger) << "request:" << std::endl
		//	<< *req;
		//ABOO_LOG_INFO(g_logger) << "response:" << std::endl
		//	<< *rsp;

		session->sendResponse(rsp);
	} while (m_isKeepalive);
	session->close();
}

}
}
