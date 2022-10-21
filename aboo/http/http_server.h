#ifndef __ABOO_HTTP_HTTP_SERVRE_H__
#define __ABOO_HTTP_HTTP_SERVRE_H__

#include "../tcp_server.h"
#include "http_session.h"
#include "servlet.h"

namespace aboo {
namespace http {

class HttpServer : public TcpServer {
public:
	typedef	std::shared_ptr<HttpServer> ptr;
	HttpServer(bool keepalive = false
			 , aboo::IOManager* worker = aboo::IOManager::GetThis()
			 , aboo::IOManager* accept_worker = aboo::IOManager::GetThis());
	ServletDispatch::ptr getServletDispath() const { return m_dispatch; }
	void setServletDispath(ServletDispatch::ptr v) { m_dispatch = v; }
protected:
	virtual void handleClient(Socket::ptr client) override;
private:
	bool m_isKeepalive;
	ServletDispatch::ptr m_dispatch;
};

}
}

#endif
