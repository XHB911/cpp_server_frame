#include "../aboo/uri.h"
#include <iostream>

int main(int argc, char** argv) {
	aboo::Uri::ptr uri = aboo::Uri::Create("http://admin@www.sylar.top:8080/test/中文/uri?id=100&name=aboo&value=中文#frg中文");
	std::cout << uri->toString() << std::endl;
	auto addr = uri->createAddress();
	std::cout << *addr << std::endl;
	return 0;
}
