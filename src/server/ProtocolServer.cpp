//
// Created by Thomas Burgaud on 14/11/2018.
//

#include <iostream>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include "protocol.hpp"
#include "ProtocolServer.hpp"

net::ProtocolServer::ProtocolServer(boost::asio::io_context &context, unsigned short port) : Server(context, port) {
}

void net::ProtocolServer::poll() {
	while (!_ioContext.stopped()) {
		_ioContext.poll();
		if (_bytesToRead) {
			handleData();
		}
	}
}

void net::ProtocolServer::handleData() {
	Header *header = reinterpret_cast<Header *>(_buff);
	if (header->op == protocolRType::PLAYER_POSITION) {
		Pos position = getDataFromBuff<Pos>(_buff);
		sendDataToAll<Pos>(position);
		_bytesToRead -= sizeof(Pos);
	}

}
