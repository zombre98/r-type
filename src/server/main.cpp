#include "ProtocolServer.hpp"

int main() {
	 boost::asio::io_context ioContext;
    net::ProtocolServer serv(ioContext, 8080);
    serv.poll();
    return 0;
}
