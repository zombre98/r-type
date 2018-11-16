//
// Created by Thomas Burgaud on 12/11/2018.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include "server.hpp"
#include "protocol.hpp"

net::server::server(ba::io_context &context, unsigned short port) :
	_ioContext{context},
	_port{port},
	_serverEndpoint(ba::ip::udp::v4(), _port),
	_socket(_ioContext, _serverEndpoint) {
	startReceive();
}

void net::server::startReceive() {
	_socket.async_receive_from(
			ba::buffer(_recvArr),
			_serverEndpoint,
			boost::bind(&server::receive, this,
					ba::placeholders::error, ba::placeholders::bytes_transferred));
	if (std::find(std::begin(_vecPort), std::end(_vecPort), _serverEndpoint.port()) == std::end(_vecPort) &&
		_serverEndpoint.port() != _port)
		_vecPort.push_back(_serverEndpoint.port());
}

void net::server::receive(const boost::system::error_code &error, std::size_t bytes_transferred) {
	if (!error || error == ba::error::message_size)
	{
		_bytesToRead = bytes_transferred;
		for (size_t i = 0; i < bytes_transferred; i++)
			_buff[i] = _recvArr[i];
		startReceive();
	}
}

std::string net::server::make_daytime_string() {
	time_t now = time(nullptr);
	return ctime(&now);
}
