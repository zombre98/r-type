//
// Created by Thomas Burgaud on 12/11/2018.
//

#include <iostream>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include "server.hpp"

net::server::server(ba::io_context &context, unsigned short port) :
	_ioContext{context},
	_port{port},
	_socket(_ioContext, {ba::ip::udp::v4(), port}) {

	startReceive();

}

void net::server::startReceive() {
	_socket.async_receive_from(
			ba::buffer(_recvBuff),
			_remote_endpoint,
			boost::bind(&server::handleReceive, this,
					ba::placeholders::error, ba::placeholders::bytes_transferred));
//	for (auto &it : recvBuff) {
//		std::cout << "it.x : " << it << std::endl;
//	}
	std::cout << std::endl;
}

void net::server::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred) {
	if (!error || error == ba::error::message_size)
	{
		char buff[bytes_transferred];
		std::cout << "Receive value size : " << bytes_transferred << std::endl;
		for (size_t i = 0; i < bytes_transferred; i++) {
			buff[i] = _recvBuff[i];
		}
		Header *header = reinterpret_cast<Header *>(buff);
		if (header->op == 1) {
			pos position = getDataFromBuff<pos>(buff);
			std::cout << "position.x : " << position.x << std::endl << "position.y : " << position.y << std::endl;
		}


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
	std::cout << "In handle send : " << *message << "size of : " << bTransferred << std::endl;

}

std::string net::server::make_daytime_string() {
	time_t now = time(nullptr);
	return ctime(&now);
}
