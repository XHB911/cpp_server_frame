#include "../aboo/application.h"

int main(int argc, char** argv) {
	aboo::Application app;
	if (app.init(argc, argv)) {
		return app.run();
	}
	return 0;
}
