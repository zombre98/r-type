//
// Created by Thomas Burgaud on 20/11/2018.
//

#pragma once

#include <string>
#include <fstream>
#include <cstdarg>

namespace log {
	enum class logLevel {
		DEBUG,
		INFO,
		ERROR
	};

	class Logger {
	public:
		Logger(std::string path);
		Logger();
		~Logger() = default;

		void log(const char *format, ...);

	public:
		static logLevel MODE;
	private:
		std::string _path;
		std::ofstream _stream{};
	};
}
