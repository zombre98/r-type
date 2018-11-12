//
// Created by Thomas Burgaud on 12/11/2018.
//

#include <iostream>
#include <boost/bind.hpp>
#include "server.hpp"

net::server::server(boost::asio::io_context &context, unsigned short port) :
	_ioContext{context},
	_port{port},
	_socket(_ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {

	//	_ioContext.run(); Maybe Useful
	startReceive();

}


void net::server::startReceive() {
	_socket.async_receive_from(
			boost::asio::buffer(_recv_buff),
			_remote_endpoint,
			boost::bind(&server::handleReceive, this,
					boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void net::server::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred) {
	if (!error || error == boost::asio::error::message_size)
	{
		boost::shared_ptr<std::string> message(
				new std::string(server::make_daytime_string()));

		_socket.async_send_to(boost::asio::buffer(*message), _remote_endpoint,
		                      boost::bind(&server::handleSend, this, message,
		                                  boost::asio::placeholders::error,
		                                  boost::asio::placeholders::bytes_transferred));

		startReceive();
	}
}

std::string net::server::make_daytime_string() {
	time_t now = time(0);
	return ctime(&now);
}

void net::server::handleSend(boost::shared_ptr<std::string> message, const boost::system::error_code &error,
                             std::size_t bTransferred) {

}
