//
// Created by armandmgt on 11/5/18.
//

#include <iostream>

int main(int argc, char *argv[]) {
	if (argc == 2) {
		std::cout << "Server started on port: " << argv[1] << std::endl;
	}
	return 0;
}
