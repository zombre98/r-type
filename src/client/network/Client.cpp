//
// Created by Thomas Burgaud on 17/11/2018.
//

#include <string>
#include "Client.hpp"
#include "events/ConnectState.hpp"

net::Client::Client(ba::io_context &context, SceneManager &_sceneManager) :
	_ioContext{context},
	_sceneManager{_sceneManager},
	_address{},
	_port{},
	_resolver{_ioContext},
	_socket{_ioContext} {
}

net::Client::~Client() {
	if (_connectionTimeout.joinable())
		_connectionTimeout.join();
}

void net::Client::connect(const std::string &address, const std::string &port) {
	_address = address;
	_port = port;
	try {
		_senderEndpoint = *_resolver.resolve(ba::ip::udp::v4(), _address, _port).begin();
	} catch (boost::exception &e) {
		_sceneManager.emit(ConnectTimeOut{});
		return;
	}
	_socket.open(ba::ip::udp::v4());
	sendData(NetPlayer{0, opCode::CONNECTION, 0});
	std::cout << "Called connect" << std::endl;
	if (_connectionTimeout.joinable())
		_connectionTimeout.join();
	_connectionTimeout = std::thread{[this]() {
		std::this_thread::sleep_for(std::chrono::seconds{5});
		if (!_connected) {
			_socket.close();
			_connecting = false;
			_sceneManager.emit(ConnectTimeOut{});
			return;
		}
	}};
	_connecting = true;
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
	if (!_connected && !_connecting)
		return;
	_ioContext.poll();
	while (!_buff.empty()) {
		handleMessage();
	}
}

void net::Client::handleMessage() {
	std::cout << "must handle message" << std::endl;
	auto head = getData<Header>();
	switch (head.op) {
	case opCode::CONNECTION : {
		std::cout << "Connection success" << std::endl;
		_connecting = false;
		_connected = true;
		auto p = getData<NetPlayer>();
		_me = p.head.id;
		_sceneManager.emit(p);
		_sceneManager.emit(ConnectSuccess{});
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
