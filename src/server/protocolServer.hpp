//
// Created by Thomas Burgaud on 14/11/2018.
//

#pragma once

#include "server.hpp"

namespace net {
	class protocolServer : public server {
	public:
		protocolServer(ba::io_context &context,unsigned short port);
		void getData();
		void poll();
	};
}