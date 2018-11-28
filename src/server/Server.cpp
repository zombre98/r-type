//
// Created by Thomas Burgaud on 12/11/2018.
//

#include <iostream>
#include <vector>
#include <boost/bind.hpp>
#include "Server.hpp"

net::Server::Server(ba::io_context &context, unsigned short port) :
	_ioContext{context},
	_port{port},
	_serverEndpoint(ba::ip::udp::v4(), _port),
	_socket(_ioContext, _serverEndpoint) {
	startReceive();
}

void net::Server::startReceive() {
	_socket.async_receive_from(ba::buffer(_recvArr), _targetEndpoint,
		boost::bind(&Server::receive, this, ba::placeholders::error, ba::placeholders::bytes_transferred));
}

void net::Server::receive(const boost::system::error_code &error, std::size_t bytes_transferred[[maybe_unused]]) {
	if (!error || error == ba::error::message_size) {
		_buff.push(_recvArr);
		startReceive();
	}
}
