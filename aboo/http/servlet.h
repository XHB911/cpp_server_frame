#ifndef __ABOO_HTTP_SERVLET_H__
#define __ABOO_HTTP_SERVLET_H__

#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include "http.h"
#include "http_session.h"
#include "../thread.h"

namespace aboo {
namespace http {

class Servlet {
public:
	typedef std::shared_ptr<Servlet> ptr;

	Servlet(const std::string& name)
		: m_name(name) {}
	virtual ~Servlet() {}
	virtual int32_t handle(aboo::http::HttpRequest::ptr request
						, aboo::http::HttpResponse::ptr response
						, aboo::http::HttpSession::ptr session) = 0;

	const std::string& getName() const { return m_name; }
protected:
	std::string m_name;
};

class FunctionServlet : public Servlet {
public:
	typedef std::shared_ptr<FunctionServlet> ptr;
	typedef std::function<int32_t (aboo::http::HttpRequest::ptr request
					, aboo::http::HttpResponse::ptr response
					, aboo::http::HttpSession::ptr session)> callback;
	FunctionServlet(callback cb);
	virtual int32_t handle(aboo::http::HttpRequest::ptr request
						, aboo::http::HttpResponse::ptr response
						, aboo::http::HttpSession::ptr session) override;
private:
	callback m_cb;
};

class ServletDispatch : public Servlet {
public:
	typedef std::shared_ptr<ServletDispatch> ptr;
	typedef RWMutex RWMutexType;

	ServletDispatch();

	int32_t handle(aboo::http::HttpRequest::ptr request
						, aboo::http::HttpResponse::ptr response
						, aboo::http::HttpSession::ptr session) override;

	void addServlet(const std::string& uri, Servlet::ptr slt);
	void addServlet(const std::string& uri, FunctionServlet::callback cb);
	void addGlobServlet(const std::string& uri, Servlet::ptr slt);
	void addGlobServlet(const std::string& uri, FunctionServlet::callback cb);

	void delServlet(const std::string& uri);
	void delGlobServlet(const std::string& uri);

	Servlet::ptr getDefault() const { return m_default; }
	void setDefault(Servlet::ptr v) { m_default = v; }

	Servlet::ptr getServlet(const std::string& uri);
	Servlet::ptr getGlobServlet(const std::string& uri);

	Servlet::ptr getMatchedServlet(const std::string& uri);
private:
	RWMutexType m_mutex;
	// url(/aboo/xxx) --> servlet; 精准匹配
	std::unordered_map<std::string, Servlet::ptr> m_datas;
	// url(/aboo/*) --> servlet;   模糊匹配
	std::vector<std::pair<std::string, Servlet::ptr>> m_globs;
	// 默认 Servlet ，所有路径未匹配到时
	Servlet::ptr m_default;
};

class NotFoundServlet : public Servlet {
public:
	typedef std::shared_ptr<NotFoundServlet> ptr;
	NotFoundServlet();
	int32_t handle(aboo::http::HttpRequest::ptr request
						, aboo::http::HttpResponse::ptr response
						, aboo::http::HttpSession::ptr session) override;
};

}
}

#endif
