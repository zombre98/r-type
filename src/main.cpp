//
// Created by armandmgt on 11/5/18.
//

#include "App.hpp"

namespace {
	std::string usage(const std::string &binaryName) {
		return "Usage: " + binaryName + " [gui | server [port]]";
	}
}

int main(int argc, char *argv[]) {
	if (argc == 2 && std::string{"gui"} == argv[1]) {
		App app;
		app.init();
		app.run();
	} else if (argc == 3 && std::string{"server"} == argv[1]) {
		std::cout << "Server started on port: " << argv[2] << std::endl;
	} else {
		std::cout << usage(argv[0]) << std::endl;
	}
	return 0;
}
