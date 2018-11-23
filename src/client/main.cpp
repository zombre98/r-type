//
// Created by armandmgt on 11/5/18.
//

#include "App.hpp"
#include "Client.hpp"

int main() {
	/*App app;
	app.init();
	app.run();
	return 0;*/
	boost::asio::io_context io_context;
	std::string addr("127.0.0.1");
	std::string port("8080");
	net::Client client(io_context, addr, port);
	net::NetPlayer p{0, net::protocolRType::CONNECTION};
	std::cout << "Size of NetPlayer : " << sizeof(net::NetPlayer) << std::endl;
	client.sendData(p);
	client.poll();
	return 0;
}
