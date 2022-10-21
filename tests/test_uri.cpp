#include "../aboo/uri.h"
#include <iostream>

int main(int argc, char** argv) {
	aboo::Uri::ptr uri = aboo::Uri::Create("http://www.sylar.top/test/uri?id=100&name=aboo*frg");
	std::cout << uri->toString() << std::endl;
	auto addr = uri->createAddress();
	std::cout << *addr << std::endl;
	return 0;
}
