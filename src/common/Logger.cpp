//
// Created by Thomas Burgaud on 20/11/2018.
//

#include <string>
#include <time.h>
#include "Logger.hpp"

log::logLevel MODE = log::logLevel::INFO;

log::Logger::Logger(std::string path) : _path(std::move(path)), _stream(path) {

}

log::Logger::Logger() : _path(""), _stream() {
	if (MODE == logLevel::INFO)
		throw std::invalid_argument("Invalid arguments in class Logger");
}

void log::Logger::log(const char *format, ...) {

}

int main() {
	log::Logger logger;
	std::string t("coucou");

	logger << t;
}

