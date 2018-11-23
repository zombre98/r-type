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
			handleData();
		}
		_sendAllPosition();
		_sendLifePoint();
	}
}

void net::ProtocolServer::handleData() {
	auto *header = reinterpret_cast<Header *>(_buff);
	if (header->op == protocolRType::POSITION) {
		auto position = getDataFromBuff<Pos>(_buff);
		sendDataToAll<Pos>(position);
	}
	if (header->op == protocolRType::CONNECTION) {
		_handleNewClient();
	}
}

void net::ProtocolServer::_handleNewClient() {
	getDataFromBuff<NetPlayer>(_buff);
	_gContainer.getWorld()->createPlayer();
	auto &entPlayer = _gContainer.getWorld()->getAllEntities()->back();
	NetPlayer plr{entPlayer->id, protocolRType::CONNECTION};
	sendDataTo(plr, _setClient.back());
	auto vec = _gContainer.getWorld()->getEntities<ecs::Player>();
	for (auto &it : vec) {
		if (it->getComponent<ecs::Player>().id != entPlayer->id) {
			NetPlayer oldPly{it->id, protocolRType::OlD_CONNECTION};
			sendDataToAll(oldPly);
		}
	}
}

void net::ProtocolServer::_sendAllPosition() {
	auto EntitiesWithPos = _gContainer.getWorld()->getEntities<ecs::Position>();
	for (auto &ent : EntitiesWithPos) {
		auto &entPos = ent->getComponent<ecs::Position>();
		Pos pos{ent->id, protocolRType::POSITION, entPos.x, entPos.y};
		sendDataToAll(pos);
	}
}

void net::ProtocolServer::_sendLifePoint() {
	auto EntitiesWithLifePoint = _gContainer.getWorld()->getEntities<ecs::LifePoint>();
	for (auto &ent : EntitiesWithLifePoint) {
		auto &entlife = ent->getComponent<ecs::LifePoint>();
		Life life{ent->id, protocolRType::LIFE_POINT, entlife.lifePoint};
		sendDataToAll(life);
	}
}

