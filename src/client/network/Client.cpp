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
	sendData(NetPlayer{0, opCode::CONNECTION});
}

void net::Client::connect(const std::string &address, const std::string &port) {
	_address = address;
	_port = port;
	_senderEndpoint = *_resolver.resolve(ba::ip::udp::v4(), _address, _port).begin();
	_socket.open(ba::ip::udp::v4());
	sendData(NetPlayer{0, opCode::CONNECTION});
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
		std::cout << "Received a message asynchronously" << std::endl;
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
	case opCode::OLD_CONNECTION : {
		auto p = getData<NetPlayer>();
		_sceneManager.emit(p);
		break;
	}
	case opCode::POSITION : {
		auto pos = getData<Pos>();
		std::cout << "Receive Pos of size " << sizeof(Pos) << std::endl;
		_sceneManager.emit(pos);
		break;
	}
	case opCode::LIFE_POINT : {
		auto life = getData<Life>();
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
		break;
	}
	default:
		break;
	}
	_buff.pop();
}
