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
		_gContainer.runSystem();
		if (_bytesToRead) {
			std::cout << "Bytes to read : " << _bytesToRead << std::endl;
			handleData();
		}
	}
}

void net::ProtocolServer::handleData() {
	auto *header = reinterpret_cast<Header *>(_buff);
	if (header->op == protocolRType::PLAYER_POSITION) {
		auto position = getDataFromBuff<Pos>(_buff);
		sendDataToAll<Pos>(position);
	}
	if (header->op == protocolRType::CONNECTION) {
		_handleNewClient();
	}
}

void net::ProtocolServer::_handleNewClient() {
	getDataFromBuff<netPlayer>(_buff);
	_gContainer.getWorld()->createPlayer();
	auto newPlayer = _gContainer.getWorld()->getEntities()->back()->getComponent<ecs::Player>();
	auto entities = _gContainer.getWorld()->getEntities();
	netPlayer plr{newPlayer.id, protocolRType::CONNECTION};
	sendDataToAll(plr);
	for (auto &it : *entities) {
		if (it->hasComponent<ecs::Player>() && it->getComponent<ecs::Player>().id != newPlayer.id) {
			netPlayer oldPly{it->getComponent<ecs::Player>().id, protocolRType::CONNECTION};
			sendDataToAll(oldPly);
		}
	}
}

