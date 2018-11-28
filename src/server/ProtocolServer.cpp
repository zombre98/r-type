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
		while (!_buff.empty())
			handleData();
		_gContainer.runSystem();
		//		_sendDeadEntities();
		//		_sendScore();
		_sendAllPosition();
		//		_sendLifePoint();
	}
}

void net::ProtocolServer::handleData() {
	auto header = getData<Header>();
	switch (header.op) {
	case opCode::CONNECTION:
		std::cout << "Received new connection" << std::endl;
		_handleNewClient();
		break;
	case opCode::POSITION: {
		auto position = getData<Pos>();
		sendDataToAll<Pos>(position);
		break;
	}
	case opCode::INPUT: {
		std::cout << "Received INPUT" << std::endl;
		_handleInput();
		break;
	}
	default:
		break;
	}
	_buff.pop();
}

void net::ProtocolServer::_handleNewClient() {
	getData<NetPlayer>();
	auto &entPlayer = _gContainer.getWorld()->createPlayer();
	_clients.emplace(entPlayer.id, _targetEndpoint);
	NetPlayer plr{entPlayer.id, opCode::CONNECTION};
	sendDataTo(_targetEndpoint, plr);
	auto vec = _gContainer.getWorld()->getEntities<ecs::Player>();
	for (auto &it : vec) {
		if (it->getComponent<ecs::Player>().id != entPlayer.id) {
			NetPlayer oldPly{it->id, opCode::OLD_CONNECTION};
			sendDataToAll(oldPly);
		}
	}
}

void net::ProtocolServer::_handleInput() {
	auto pkg = getData<Input>();
	if (auto entity = _gContainer.getWorld()->getEntity(pkg.head.id)) {
		(*entity)->getComponent<ecs::Input>().input[pkg.action] = true;
	}
}

void net::ProtocolServer::_sendAllPosition() {
	auto const &EntitiesWithPos = _gContainer.getWorld()->getEntities<ecs::Position>();
	for (auto const &ent : EntitiesWithPos) {
		auto &compPos = ent->getComponent<ecs::Position>();
		if (compPos.updated) {
			sendDataToAll(Pos{ent->id, opCode::POSITION, compPos.x, compPos.y});
			compPos.updated = false;
		}
	}
}

void net::ProtocolServer::_sendLifePoint() {
	auto const &EntitiesWithLifePoint = _gContainer.getWorld()->getEntities<ecs::LifePoint>();
	for (auto const &ent : EntitiesWithLifePoint) {
		auto &compLife = ent->getComponent<ecs::LifePoint>();
		if (compLife.updated) {
			sendDataToAll(Life{ent->id, compLife.lifePoint});
			compLife.updated = false;
		}
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

