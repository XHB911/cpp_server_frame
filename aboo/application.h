#ifndef __ABOO_APPLICATION_H__
#define __ABOO_APPLICATION_H__

#include "http/http_server.h"

namespace aboo {

class Application {
public:
	Application();

	static Application* GetInstance() { return s_instance; }
	bool init(int argc, char** argv);
	bool run();
private:
	int	main(int argc, char** argv);
	int run_fibler();
private:
	int m_argc = 0;
	char** m_argv = nullptr;

	std::vector<aboo::http::HttpServer::ptr> m_httpservers;
	static Application* s_instance;
};

}

#endif
