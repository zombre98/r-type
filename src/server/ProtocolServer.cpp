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
		_sendDeadEntities();
		//		_sendScore();
		_sendNewShoot();
		_sendAllEnemies();
		_sendAllPosition();
		//		_sendLifePoint();
	}
}

void net::ProtocolServer::handleData() {
	auto header = getData<Header>();
	switch (header.op) {
	case opCode::CONNECTION:
		_handleNewClient();
		break;
	case opCode::POSITION: {
		auto position = getData<Pos>();
		sendDataToAll<Pos>(position);
		break;
	}
	case opCode::INPUT: {
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
	auto playerId = entPlayer.getComponent<ecs::Player>().id;
	_clients.emplace(entPlayer.id, _targetEndpoint);
	NetPlayer plr{entPlayer.id, opCode::CONNECTION, playerId};
	sendDataTo(_targetEndpoint, plr);
	sendDataToAllExcept(_targetEndpoint, NetPlayer{entPlayer.id, opCode::NEW_CONNECTION, playerId});
	auto vec = _gContainer.getWorld()->getEntities<ecs::Player>();
	for (auto &it : vec) {
		auto othId = it->getComponent<ecs::Player>().id;
		if (othId != entPlayer.id) {
			NetPlayer oldPly{it->id, opCode::OLD_CONNECTION, othId};
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
		if (ent->hasComponent<ecs::LifePoint>() && ent->getComponent<ecs::LifePoint>().lifePoint <= 0)
			continue;
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

void net::ProtocolServer::_sendAllEnemies() {
	auto const &EntitiesWithEnemies =  _gContainer.getWorld()->getEntities<ecs::EnemyType>();
	for (auto const &ent : EntitiesWithEnemies) {
		auto &compEnemyType = ent->getComponent<ecs::EnemyType>();
		if (compEnemyType.updated) {
			EnemyType eType = {ent->id, compEnemyType.type};
			sendDataToAll(eType);
			compEnemyType.updated = false;
		}
	}
}

void net::ProtocolServer::_sendNewShoot() {
	auto const &EntitiesWithShootType =  _gContainer.getWorld()->getEntities<ecs::ShotType>();
	for (auto const &ent : EntitiesWithShootType) {
		auto &compShot = ent->getComponent<ecs::ShotType>();
		if (compShot.updated) {
			ShotType shot{ent->id, compShot.type};
			sendDataToAll(shot);
			compShot.updated = false;
		}
	}
}

