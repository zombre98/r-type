//
// Created by Thomas Burgaud on 12/11/2018.
//

#include <iostream>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include "server.hpp"
#include "protocol.hpp"

net::server::server(ba::io_context &context, unsigned short port) :
	_ioContext{context},
	_port{port},
	_socket(_ioContext, {ba::ip::udp::v4(), port}) {

	startReceive();

}

void net::server::startReceive() {
	_socket.async_receive_from(
			ba::buffer(_recvArr),
			_remote_endpoint,
			boost::bind(&server::receive, this,
					ba::placeholders::error, ba::placeholders::bytes_transferred));
}

void net::server::receive(const boost::system::error_code &error, std::size_t bytes_transferred) {
	if (!error || error == ba::error::message_size)
	{
		lastTransfer = bytes_transferred;
		for (size_t i = 0; i < bytes_transferred; i++)
			_buff[i] = _recvArr[i];


		auto message = boost::make_shared<std::string>(server::make_daytime_string());
		_socket.async_send_to(ba::buffer(*message), _remote_endpoint,
		                      boost::bind(&server::handleSend, this, message,
		                                  ba::placeholders::error,
		                                  ba::placeholders::bytes_transferred));
		startReceive();
	}
}

void net::server::handleSend(boost::shared_ptr<std::string> message, const boost::system::error_code &error,
                             std::size_t bTransferred) {
}

std::string net::server::make_daytime_string() {
	time_t now = time(nullptr);
	return ctime(&now);
}
