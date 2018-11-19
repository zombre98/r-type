//
// Created by Thomas Burgaud on 17/11/2018.
//

#include <string>
#include <iostream>
#include "client.hpp"

net::client::client(boost::asio::io_context &context, std::string &address, std::string &port) :
_ioContext{context},
_address{address},
_port{port},
_resolver{_ioContext},
_senderEndpoint{*_resolver.resolve(ba::ip::udp::v4(), address, port).begin()},
_socket{_ioContext}
{
	_socket.open(ba::ip::udp::v4());
}

net::Header net::client::getHeaderAndReadBuff() {
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

void net::client::asyncReceive() {
	_socket.async_receive_from(
			ba::buffer(_recvArr),
			_receiverEndpoint,
			boost::bind(&client::receive, this,
			            ba::placeholders::error, ba::placeholders::bytes_transferred));
}

void net::client::receive(const boost::system::error_code &error, std::size_t bytes_transferred) {
	if (!error || error == ba::error::message_size)
	{
		for (size_t i = 0; i < bytes_transferred; i++)
			_buff[i] = _recvArr[i];
		Header head = getDataFromBuff<Header>(_buff);
		std::cout << "Head id : " << head.id << std::endl;
		asyncReceive();
	}
}

void net::client::poll() {
	asyncReceive();
	while (!_ioContext.stopped()) {
		_ioContext.poll();
	}
}
