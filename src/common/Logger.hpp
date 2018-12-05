//
// Created by armandmgt on 12/3/18.
//

#pragma once

#include <iostream>
#include <fstream>
#include <memory>

namespace logging {
	template<typename T>
	struct logger : T {
		explicit logger(std::streambuf *sb) :
			std::ostream{sb} {
		};

		explicit logger(std::ofstream &&rhs) :
			std::ofstream{std::move(rhs)} {
		};
	};

	inline logger<std::ostream> debug(std::cout.rdbuf());

	inline logger<std::ofstream> info(std::ofstream("log.txt"));

	inline logger<std::ostream> error(std::cerr.rdbuf());
}
