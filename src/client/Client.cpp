//
// Created by Thomas Burgaud on 17/11/2018.
//

#include <string>
#include <iostream>
#include "Client.hpp"

net::Client::Client(ba::io_context &context, std::string &address, std::string &port) :
_ioContext{context},
_address{address},
_port{port},
_resolver{_ioContext},
_senderEndpoint{*_resolver.resolve(ba::ip::udp::v4(), address, port).begin()},
_socket{_ioContext}
{
	_socket.open(ba::ip::udp::v4());
}

net::Header net::Client::getHeaderAndReadBuff() {
	boost::array<char, 128> recvArr{};
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
	_socket.async_receive_from(
			ba::buffer(_recvArr),
			_receiverEndpoint,
			boost::bind(&Client::receive, this,
			            ba::placeholders::error, ba::placeholders::bytes_transferred));
}

void net::Client::receive(const boost::system::error_code &error, std::size_t bytes_transferred) {
	if (!error || error == ba::error::message_size)
	{
		for (size_t i = 0; i < bytes_transferred; i++)
			_buff[i] = _recvArr[i];
		auto head = getDataFromBuff<Header>(_buff);
		if (head.op == protocolRType::CONNECTION) {
			auto p = getData<NetPlayer>();
			//std::cout << "I'm connected with id : " << p.head.id << std::endl;
		}
		if (head.op == protocolRType::OlD_CONNECTION) {
			auto p = getData<NetPlayer>();
			//std::cout << "Other Player id : " << p.head.id << std::endl;
		}
		if (head.op == protocolRType::POSITION) {
			auto pos = getData<Pos>();
			//std::cout << "Head : " << pos.head.id << " Receive Pos : X " << pos.x  << " Y " << pos.y << std::endl;
		}
		if (head.op == protocolRType::LIFE_POINT) {
			auto life = getData<Life>();
			//std::cout << "Id : " << life.head.id << " LifePoint = " << life.lifePoint << std::endl;
		}
		if (head.op == protocolRType::SCORE) {
			auto score = getData<Score>();
			//std::cout << "Score : " << score.score << std::endl;
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
