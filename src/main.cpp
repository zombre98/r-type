//
// Created by armandmgt on 11/5/18.
//

#include <iostream>
#include <protocol.hpp>
#include "server/server.hpp"
#include "server/protocolServer.hpp"

int main() {
	boost::asio::io_context ioContext;
	net::protocolServer serv(ioContext, 8080);
	serv.poll();
}
