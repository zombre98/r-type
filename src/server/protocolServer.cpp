//
// Created by Thomas Burgaud on 14/11/2018.
//

#include <iostream>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include "protocol.hpp"
#include "protocolServer.hpp"

net::protocolServer::protocolServer(boost::asio::io_context &context, unsigned short port) : server(context, port) {
}

void net::protocolServer::poll() {
	while (!_ioContext.stopped()) {
		_ioContext.poll();
		if (_bytesToRead) {
			std::cout << "I value : " << _bytesToRead << std::endl;
			getData();
		}
	}
}

void net::protocolServer::getData() {
	Header *header = reinterpret_cast<Header *>(_buff);
	if (header->op == protocolRType::PLAYER_POSITION) {
		Pos position = getDataFromBuff<Pos>(_buff);
		std::cout << "position.x : " << position.x << std::endl << "position.y : " << position.y << std::endl;
		sendDataToAll<Pos>(position);
		_bytesToRead -= sizeof(Pos);
	}

}

