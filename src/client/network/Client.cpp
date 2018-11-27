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
}

void net::Client::connect(const std::string &address, const std::string &port) {
	_address = address;
	_port = port;
	_senderEndpoint = *_resolver.resolve(ba::ip::udp::v4(), _address, _port).begin();
	_socket.open(ba::ip::udp::v4());
	std::cout << "Called connect on socket" << std::endl;
}

net::Header net::Client::getHeaderAndReadBuff() {
	boost::array<char, READ_SIZE> recvArr{};
	_bytesReceived = _socket.receive_from(ba::buffer(recvArr), _receiverEndpoint);
	for (size_t i = 0; i < _bytesReceived; i++)
		_buff[i] = recvArr[i];
	Header returnHeader{};
	if (_bytesReceived) {
		auto header = reinterpret_cast<Header *>(_buff);
		returnHeader = *header;
	}
	return returnHeader;
}

void net::Client::asyncReceive() {
	_socket.async_receive_from(ba::buffer(_recvArr), _receiverEndpoint,
	                           boost::bind(&Client::receive, this, ba::placeholders::error, ba::placeholders::bytes_transferred));
}

void net::Client::receive(const boost::system::error_code &error, std::size_t bytes_transferred) {
	if (!error || error == ba::error::message_size)
	{
		for (size_t i = 0; i < bytes_transferred; i++)
			_buff[i] = _recvArr[i];
		auto head = getDataFromBuff<Header>(_buff);
		switch (head.op) {
			case protocolRType::CONNECTION : {
				auto p = getData<NetPlayer>();
				std::cout << "I'm connected with id : " << p.head.id << std::endl;
				break;
			}
			case protocolRType::OLD_CONNECTION : {
				auto p = getData<NetPlayer>();
				std::cout << "Other Player id : " << p.head.id << std::endl;
				break;
			}
			case protocolRType::POSITION : {
				auto pos = getData<Pos>();
				std::cout << "Head : " << pos.head.id << " Receive Pos : X " << pos.x  << " Y " << pos.y << std::endl;
				break;
			}
			case protocolRType::LIFE_POINT : {
				auto life = getData<Life>();
				std::cout << "Id : " << life.head.id << " LifePoint = " << life.lifePoint << std::endl;
				break;
			}
			case protocolRType::SCORE : {
				auto score = getData<Score>();
				std::cout << "Score : " << score.score << std::endl;
				break;
			}
			case protocolRType::DEAD : {
				auto dead = getData<Dead>();
				break;
			}
			default:
				break;
		}
		/*
		 * You need to add the handle of all struct here
		 */
		asyncReceive();
	}
}

void net::Client::poll() {
	asyncReceive();
	while (!_ioContext.stopped()) {
		_ioContext.poll();
	}
}

void net::Client::pollOnce() {
	asyncReceive();
	if (!_ioContext.stopped()) {
		_ioContext.poll_one();
	}
}
