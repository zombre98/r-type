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
		while (!_buff.empty()) {
			handleData();
		}
		_sendDeadEntities();
		_sendScore();
		_sendAllPosition();
		_sendLifePoint();
	}
}

void net::ProtocolServer::handleData() {
	auto header = reinterpret_cast<Header *>(_buff.front().elems);
	//	std::cout << static_cast<int>(header->op) << std::endl;
	switch (header->op) {
	case opCode::CONNECTION:
		//		std::cout << "Handle New connection" << std::endl;
		_handleNewClient();
		break;
	case opCode::POSITION: {
		auto position = getDataFromBuff<Pos>();
		sendDataToAll<Pos>(position);
		break;
	}
	case opCode::INPUT: {
		std::cout << "Received INPUT" << std::endl;
		_handleInput();
	}
	default:
		break;
	}
}

void net::ProtocolServer::_handleNewClient() {
	//	std::cout << "Handle New Client" << std::endl;
	getDataFromBuff<NetPlayer>();
	_gContainer.getWorld()->createPlayer();
	auto &entPlayer = _gContainer.getWorld()->getAllEntities()->back();
	NetPlayer plr{entPlayer->id, opCode::CONNECTION};
	sendDataTo(plr, _setClient.back());
	auto vec = _gContainer.getWorld()->getEntities<ecs::Player>();
	for (auto &it : vec) {
		if (it->getComponent<ecs::Player>().id != entPlayer->id) {
			NetPlayer oldPly{it->id, opCode::OLD_CONNECTION};
			sendDataToAll(oldPly);
		}
	}
}

void net::ProtocolServer::_handleInput() {
	auto input = getDataFromBuff<Input>();
	if (auto entity = _gContainer.getWorld()->getEntity(input.head.id)) {
		(*entity)->getComponent<ecs::Input>() = ecs::Input{input.action};
	}
}

void net::ProtocolServer::_sendAllPosition() {
	auto const &EntitiesWithPos = _gContainer.getWorld()->getEntities<ecs::Position>();
	for (auto const &ent : EntitiesWithPos) {
		auto const &entPos = ent->getComponent<ecs::Position>();
		Pos pos{ent->id, opCode::POSITION, entPos.x, entPos.y};
		sendDataToAll(pos);
	}
}

void net::ProtocolServer::_sendLifePoint() {
	auto const &EntitiesWithLifePoint = _gContainer.getWorld()->getEntities<ecs::LifePoint>();
	for (auto const &ent : EntitiesWithLifePoint) {
		auto const &compLife = ent->getComponent<ecs::LifePoint>();
		Life life{ent->id, compLife.lifePoint};
		sendDataToAll(life);
	}
}

void net::ProtocolServer::_sendScore() {
	auto const &EntitiesWithScore =  _gContainer.getWorld()->getEntities<ecs::Score>();
	for (auto const &ent : EntitiesWithScore) {
		auto const &compScore = ent->getComponent<ecs::Score>();
		Score score{ent->id, compScore.score};
		sendDataToAll(score);
	}
}

void net::ProtocolServer::_sendDeadEntities() {
	auto const &EntityWithLifePoint = _gContainer.getWorld()->getEntities<ecs::LifePoint, ecs::Position>();
	for (auto const &ent : EntityWithLifePoint) {
		auto const &compLife = ent->getComponent<ecs::LifePoint>();
		auto const &compPos = ent->getComponent<ecs::Position>();
		if (compLife.lifePoint <= 0) {
			Dead dead{ent->id, compPos.x, compPos.y};
			sendDataToAll(dead);
		}
	}
}

