//
// Created by armandmgt on 11/5/18.
//

#include <iostream>
#include "server/server.hpp"

int main() {
	boost::asio::io_context ioContext;
	net::server serv(ioContext, 13);
	ioContext.run();
}
