#include <iostream>
#include "protocol.hpp"
#include "server.hpp"
#include "protocolServer.hpp"

int main() {
	boost::asio::io_context ioContext;
	net::protocolServer serv(ioContext, 8080);
	serv.poll();
}
