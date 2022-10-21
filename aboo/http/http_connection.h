#ifndef __ABOO_HTTP_CONNECTIONI_H__
#define __ABOO_HTTP_CONNECTIONI_H__

#include "../socket_stream.h"
#include "http.h"

namespace aboo {
namespace http {

class HttpConnection : public SocketStream {
public:
	typedef std::shared_ptr<HttpConnection> ptr;
	HttpConnection(Socket::ptr sock, bool owner = true);
	HttpResponse::ptr recvResponse();
	int sendRequest(HttpRequest::ptr req);
};

}
}

#endif
