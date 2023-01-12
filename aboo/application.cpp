#include "application.h"
#include "config.h"
#include "env.h"
#include "log.h"
#include "daemon.h"
#include "http/http_server.h"
#include <unistd.h>

namespace aboo {

static aboo::Logger::ptr g_logger = ABOO_LOG_NAME("system");

static aboo::ConfigVar<std::string>::ptr g_server_work_path =
	aboo::Config::Lookup("server.work_path", std::string("/apps/work/aboo"), "server work path");

static aboo::ConfigVar<std::string>::ptr g_server_pid_file =
	aboo::Config::Lookup("server.pid_file", std::string("aboo.pid"), "server pid file");

struct HttpServerConf {
	std::vector<std::string> address;
	int keepalive = 0;
	int timeout = 1000 * 2 * 60;
	std::string name;

	bool isValid() const {
		return !address.empty();
	}

	bool operator==(const HttpServerConf& oth) const {
		return address == oth.address && keepalive == oth.keepalive && timeout == oth.timeout && name == oth.name;
	}
};

template<>
class LexicalCast<std::string, HttpServerConf> {
public:
	HttpServerConf operator()(const std::string& v) {
		YAML::Node node = YAML::Load(v);
		HttpServerConf conf;
		conf.keepalive = node["keepalive"].as<int>(conf.keepalive);
		conf.timeout = node["timeout"].as<int>(conf.timeout);
		conf.name = node["name"].as<std::string>(conf.name);
		if (node["address"].IsDefined()) {
			for (size_t i = 0; i < node["address"].size(); ++i) {
				conf.address.push_back(node["address"][i].as<std::string>());
			}
		}
		return conf;
	}
};

template<>
class LexicalCast<HttpServerConf, std::string> {
public:
	std::string operator()(const HttpServerConf& conf) {
		YAML::Node node;
		node["name"] = conf.name;
		node["keepalive"] = conf.keepalive;
		node["timeout"] = conf.timeout;
		for (auto& i : conf.address) {
			node["address"].push_back(i);
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

static aboo::ConfigVar<std::vector<HttpServerConf>>::ptr g_http_servers_conf =
	aboo::Config::Lookup("http_servers", std::vector<HttpServerConf>(), "http server config");

Application* Application::s_instance = nullptr;

Application::Application() {
	s_instance = this;
}

bool Application::init(int argc, char** argv) {
	m_argc = argc;
	m_argv = argv;

	aboo::EnvMgr::getInstance()->addHelp("s", "start whit the terminal");
	aboo::EnvMgr::getInstance()->addHelp("d", "run as daemon");
	aboo::EnvMgr::getInstance()->addHelp("c", "conf path default: ./conf");
	aboo::EnvMgr::getInstance()->addHelp("p", "print help");

	if (!aboo::EnvMgr::getInstance()->init(argc, argv)) {
		aboo::EnvMgr::getInstance()->printHelp();
		return false;
	}

	if (aboo::EnvMgr::getInstance()->has("p")) {
		aboo::EnvMgr::getInstance()->printHelp();
		return false;
	}

	int run_type = 0;
	if (aboo::EnvMgr::getInstance()->has("s")) {
		run_type = 1;
	}

	if (aboo::EnvMgr::getInstance()->has("d")) {
		run_type = 2;
	}

	if (run_type == 0) {
		aboo::EnvMgr::getInstance()->printHelp();
		return false;
	}

	std::string pidfile = g_server_work_path->getValue() + "/" + g_server_pid_file->getValue();
	if (aboo::FSUtil::IsRunningPidfile(pidfile)) {
		ABOO_LOG_ERROR(g_logger) << "server is running:" << pidfile;
		return false;
	}

	std::string conf_path = aboo::EnvMgr::getInstance()->getAbsolutePath(aboo::EnvMgr::getInstance()->get("c", "conf"));
	ABOO_LOG_INFO(g_logger) << "load conf path:" << conf_path;
	aboo::Config::LoadFromConfDir(conf_path);

	if (!aboo::FSUtil::Mkdir(g_server_work_path->getValue())) {
		ABOO_LOG_FATAL(g_logger) << "create work path [" << g_server_work_path->getValue()
								 << "] error=" << errno << " strerr=" << strerror(errno);
		return false;
	}

	return true;
}

bool Application::run() {
	bool is_daemon = aboo::EnvMgr::getInstance()->has("d");
	return start_daemon(m_argc, m_argv
			, std::bind(&Application::main, this, std::placeholders::_1
				, std::placeholders::_2), is_daemon);
}

int Application::main(int argc, char** argv) {
	std::string pidfile = g_server_work_path->getValue() + "/" + g_server_pid_file->getValue();
	std::ofstream ofs(pidfile);
	if (!ofs) {
		ABOO_LOG_ERROR(g_logger) << "open pidfile " << pidfile << " failed";
		return false;
	}
	ofs << getpid();

	aboo::IOManager iom(1);
	iom.schedule(std::bind(&Application::run_fibler, this));
	iom.stop();

	return 0;
}

int Application::run_fibler(){
	auto http_confs = g_http_servers_conf->getValue();
	for (auto& i : http_confs) {
		ABOO_LOG_INFO(g_logger) << LexicalCast<HttpServerConf, std::string>()(i);

		std::vector<Address::ptr> address;
		for (auto& a : i.address) {
			size_t pos = a.find(":");
			if (pos == std::string::npos) {
				ABOO_LOG_ERROR(g_logger) << "invalid address: " << a;
				continue;
			}
			auto addr = aboo::Address::LookupAny(a);
			if (addr) {
				address.push_back(addr);;
				continue;
			}
			std::vector<std::pair<Address::ptr, uint32_t>> result;
			if (!aboo::Address::GetInterfaceAddresses(result, a.substr(0, pos))) {
				ABOO_LOG_ERROR(g_logger) << "invalid address: " << a;
				continue;
			}
			for (auto& x : result) {
				auto ipaddr = std::dynamic_pointer_cast<IPAddress>(x.first);
				if (ipaddr) ipaddr->setPort(atoi(a.substr(pos + 1).c_str()));
				address.push_back(ipaddr);
			}
		}
		aboo::http::HttpServer::ptr server(new aboo::http::HttpServer(i.keepalive));
		std::vector<Address::ptr> fails;
		if (!server->bind(address, fails)) {
			for (auto& x : fails) {
				ABOO_LOG_ERROR(g_logger) << "bind address fail:" << *x;
			}
			_exit(0);
		}
		if (!i.name.empty()) {
			server->setName(i.name);
		}
		server->start();
		m_httpservers.push_back(server);
	}
	return 0;
}

}
