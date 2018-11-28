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
		_sendDeadEntities();
		_sendScore();
		_sendAllPosition();
		_sendLifePoint();
	}
}

void net::ProtocolServer::handleData() {
	auto header = reinterpret_cast<Header *>(_buff.front());
	std::cout << "I have : " << _bytesToRead << " bytes to read" << std::endl;
	std::cout << static_cast<int>(header->op) << std::endl;
	if (header->op == protocolRType::CONNECTION) {
		std::cout << "Handle New connection" << std::endl;
		_handleNewClient();
	}
	if (header->op == protocolRType::POSITION) {
		auto position = getDataFromBuff<Pos>(_buff.front());
		sendDataToAll<Pos>(position);
	}
}

void net::ProtocolServer::_handleNewClient() {
	std::cout << "Handle New Client" << std::endl;
	getDataFromBuff<NetPlayer>(_buff.front());
	_gContainer.getWorld()->createPlayer();
	auto &entPlayer = _gContainer.getWorld()->getAllEntities()->back();
	NetPlayer plr{entPlayer->id, protocolRType::CONNECTION};
	sendDataTo(plr, _setClient.back());
	auto vec = _gContainer.getWorld()->getEntities<ecs::Player>();
	for (auto &it : vec) {
		if (it->getComponent<ecs::Player>().id != entPlayer->id) {
			NetPlayer oldPly{it->id, protocolRType::OLD_CONNECTION};
			sendDataToAll(oldPly);
		}
	}
}

void net::ProtocolServer::_sendAllPosition() {
	auto const &EntitiesWithPos = _gContainer.getWorld()->getEntities<ecs::Position>();
	for (auto const &ent : EntitiesWithPos) {
		auto const &entPos = ent->getComponent<ecs::Position>();
		Pos pos{ent->id, protocolRType::POSITION, entPos.x, entPos.y};
		sendDataToAll(pos);
	}
}

void net::ProtocolServer::_sendLifePoint() {
	auto const &EntitiesWithLifePoint = _gContainer.getWorld()->getEntities<ecs::LifePoint>();
	for (auto const &ent : EntitiesWithLifePoint) {
		auto const &compLife = ent->getComponent<ecs::LifePoint>();
		Life life{ent->id, protocolRType::LIFE_POINT, compLife.lifePoint};
		sendDataToAll(life);
	}
}

void net::ProtocolServer::_sendScore() {
	auto const &EntitiesWithScore =  _gContainer.getWorld()->getEntities<ecs::Score>();
	for (auto const &ent : EntitiesWithScore) {
		auto const &compScore = ent->getComponent<ecs::Score>();
		Score score{ent->id, protocolRType::SCORE, compScore.score};
		sendDataToAll(score);
	}
}

void net::ProtocolServer::_sendDeadEntities() {
	auto const &EntityWithLifePoint = _gContainer.getWorld()->getEntities<ecs::LifePoint, ecs::Position>();
	for (auto const &ent : EntityWithLifePoint) {
		auto const &compLife = ent->getComponent<ecs::LifePoint>();
		auto const &compPos = ent->getComponent<ecs::Position>();
		if (compLife.lifePoint <= 0) {
			Dead dead{ent->id, protocolRType::DEAD, compPos.x, compPos.y};
			sendDataToAll(dead);
		}
	}
}

