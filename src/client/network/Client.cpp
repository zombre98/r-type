//
// Created by Thomas Burgaud on 17/11/2018.
//

#include <string>
#include "Client.hpp"

net::Client::Client(ba::io_context &context, SceneManager &_sceneManager) :
	_ioContext{context},
	_sceneManager{_sceneManager},
	_address{},
	_port{},
	_resolver{_ioContext},
	_socket{_ioContext} {
}

net::Client::Client(ba::io_context &context, SceneManager &_sceneManager, const std::string &address,
	const std::string &port) :
	_ioContext{context},
	_sceneManager{_sceneManager},
	_address{address},
	_port{port},
	_resolver{_ioContext},
	_senderEndpoint{*_resolver.resolve(ba::ip::udp::v4(), address, port).begin()},
	_socket{_ioContext} {
	_socket.open(ba::ip::udp::v4());
	sendData(NetPlayer{0, opCode::CONNECTION, 0});
}

void net::Client::connect(const std::string &address, const std::string &port) {
	_address = address;
	_port = port;
	_senderEndpoint = *_resolver.resolve(ba::ip::udp::v4(), _address, _port).begin();
	_socket.open(ba::ip::udp::v4());
	sendData(NetPlayer{0, opCode::CONNECTION, 0});
	std::cout << "Called connect" << std::endl;
	auto bytesRead = _socket.receive_from(ba::buffer(_recvArr), _receiverEndpoint);
	if (bytesRead)
		_buff.push(_recvArr);
	_connected = true;
	asyncReceive();
}

void net::Client::asyncReceive() {
	_socket.async_receive_from(ba::buffer(_recvArr), _receiverEndpoint,
		boost::bind(&Client::receive, this, ba::placeholders::error, ba::placeholders::bytes_transferred));
}

void net::Client::receive(const boost::system::error_code &error, std::size_t bytes_transferred[[maybe_unused]]) {
	if (!error || error == ba::error::message_size) {
		_buff.push(_recvArr);
	}
	asyncReceive();
}

void net::Client::poll() {
	if (!_connected)
		return;
	_ioContext.poll();
	while (!_buff.empty()) {
		handleMessage();
	}
}

void net::Client::handleMessage() {
	auto head = getData<Header>();
	switch (head.op) {
	case opCode::CONNECTION : {
		auto p = getData<NetPlayer>();
		std::cout << "Connection success" << std::endl;
		_me = p.head.id;
		_sceneManager.emit(p);
		break;
	}
	case opCode::NEW_CONNECTION :
	case opCode::OLD_CONNECTION : {
		_sceneManager.emit(getData<NetPlayer>());
		break;
	}
	case opCode::POSITION : {
		auto pos = getData<Pos>();
		_sceneManager.emit(pos);
		break;
	}
	case opCode::LIFE_POINT : {
		auto life = getData<Life>();
		_sceneManager.emit<Life>(life);
		//			std::cout << "Id : " << life.head.id << " LifePoint = " << life.lifePoint << std::endl;
		break;
	}
	case opCode::SCORE : {
		auto score = getData<Score>();
		//			std::cout << "Score : " << score.score << std::endl;
		break;
	}
	case opCode::DEAD : {
		auto dead = getData<Dead>();
		_sceneManager.emit(dead);
		break;
	}
	case opCode::NEW_ENEMY : {
		auto enemy = getData<EnemyType>();
		_sceneManager.emit(enemy);
		break;
	}
	case opCode::NEW_SHOT : {
		auto shot = getData<ShotType>();
		_sceneManager.emit(shot);
	}
	default:
		break;
	}
	_buff.pop();
}
