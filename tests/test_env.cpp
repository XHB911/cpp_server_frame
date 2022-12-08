#include "../aboo/env.h"
#include <unistd.h>
#include <fstream>
#include <iostream>

struct A {
	A() {
		std::ifstream ifs("/proc/" + std::to_string(getpid()) + "/cmdline", std::ios::binary);
		std::string content;
		content.resize(4096);

		ifs.read(&content[0], content.size());
		content.resize(ifs.gcount());

		for (size_t i = 0; i < content.size(); ++i) {
			std::cout << i << " - " << content[i] << " - " << (int)content[i] << std::endl;
		}
		std::cout << content << std::endl;
	}
};

A a;

int main(int argc, char** argv) {
	aboo::EnvMgr::getInstance()->addHelp("s", "start with the terminal");
	aboo::EnvMgr::getInstance()->addHelp("d", "run as daemon");
	aboo::EnvMgr::getInstance()->addHelp("p", "print help");
	if (!aboo::EnvMgr::getInstance()->init(argc, argv)) {
		aboo::EnvMgr::getInstance()->printHelp();
		return 0;
	}

	std::cout << "exe=" << aboo::EnvMgr::getInstance()->getExe() << std::endl;
	std::cout << "cwd=" << aboo::EnvMgr::getInstance()->getCwd() << std::endl;

	std::cout << "path=" << aboo::EnvMgr::getInstance()->getEnv("PATH", "xxx") << std::endl;
	std::cout << "test=" << aboo::EnvMgr::getInstance()->getEnv("TEST", "yyy") << std::endl;
	std::cout << "set env " << aboo::EnvMgr::getInstance()->setEnv("TEST", "yyy") << std::endl;
	std::cout << "test=" << aboo::EnvMgr::getInstance()->getEnv("TEST", "yyy") << std::endl;

	if (aboo::EnvMgr::getInstance()->has("p")) {
		aboo::EnvMgr::getInstance()->printHelp();
	}
	return 0;
}
