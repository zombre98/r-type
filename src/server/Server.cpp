//
// Created by Thomas Burgaud on 12/11/2018.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include "Server.hpp"
#include "protocol.hpp"

net::Server::Server(ba::io_context &context, unsigned short port) :
	_ioContext{context},
	_port{port},
	_serverEndpoint(ba::ip::udp::v4(), _port),
	_socket(_ioContext, _serverEndpoint) {
	startReceive();
}

void net::Server::startReceive() {
	_socket.async_receive_from(
			ba::buffer(_recvArr),
			_serverEndpoint,
			boost::bind(&Server::receive, this,
					ba::placeholders::error, ba::placeholders::bytes_transferred));
	if (_serverEndpoint.port() != _port) {
		_setClient.emplace_back(_serverEndpoint.address(), _serverEndpoint.port());
	}
}

void net::Server::receive(const boost::system::error_code &error, std::size_t bytes_transferred) {
	if (!error || error == ba::error::message_size)
	{
		_bytesToRead += bytes_transferred;
		_buff.emplace();
		std::cout << _bytesToRead << " = " << sizeof(NetPlayer) << std::endl;
		for (size_t i = 0; i < bytes_transferred; i++)
			_buff.back()[i] = _recvArr[i];
		startReceive();
	}
}
