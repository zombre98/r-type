//
// Created by Thomas Burgaud on 17/11/2018.
//

#include <string>
#include <iostream>
#include "client.hpp"

net::client::client(boost::asio::io_context &context, std::string &address, std::string &port) :
_ioContext{context},
_address{address},
_port{port},
_resolver{_ioContext},
_senderEndpoint{*_resolver.resolve(ba::ip::udp::v4(), address, port).begin()},
_socket{_ioContext}
{
	_socket.open(ba::ip::udp::v4());
}

net::Header net::client::getHeaderAndReadBuff() {
	boost::array<char, 128> recvArr{};
	_bytesReceived = _socket.receive_from(boost::asio::buffer(recvArr), _receiverEndpoint);
	for (size_t i = 0; i < _bytesReceived; i++)
		_buff[i] = recvArr[i];
	Header returnHeader;
	if (_bytesReceived) {
		auto header = reinterpret_cast<Header *>(_buff);
		returnHeader = *header;
	}
	return returnHeader;
}

/*
int main()
{
	boost::asio::io_context io_context;
	std::string addr("127.0.0.1");
	std::string port("8080");

	net::client Client(io_context, addr, port);
	net::Header head{15, net::protocolRType::PLAYER_POSITION};
	net::Pos pos{head, 15, 40};
	Client.sendData<net::Pos>(pos);
	while (1) {
		net::Header newhead = Client.getHeaderAndReadBuff();
		net::Pos position{};
		if (newhead.op == net::protocolRType::PLAYER_POSITION)
			position = Client.getData<net::Pos>();
		std::cout << "Position x : " << position.x << " Position y : " << position.y << std::endl;
	}
	return 0;
}*/