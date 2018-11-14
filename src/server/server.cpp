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
	static boost::array<char, 1> recvBuff = {};

	_socket.async_receive_from(
			ba::buffer(recvBuff),
			_remote_endpoint,
			boost::bind(&server::handleReceive, this,
					ba::placeholders::error, ba::placeholders::bytes_transferred));
	char buff[sizeof(recvBuff[0])];
	std::cout << "Receive value : " << ba::placeholders::bytes_transferred << std::endl;
	for (size_t i = 0; i < sizeof(recvBuff[0]); i++) {
		buff[i] = recvBuff[i];
	}
	Header header{};
	for (auto i = 0; i < sizeof(Header); i++)
		std::memcpy(&header+i, &buff[i], 1);
	std::cout << "Header id : " << header.id << std::endl;
	std::cout << "Header op : " << header.op << std::endl;
	std::cout << "Pos structure size = " << sizeof(pos) << std::endl;
	for (auto &it : recvBuff) {
		std::cout << "it.x : " << it << std::endl;
	}
	std::cout << std::endl;
}

void net::server::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred) {
	if (!error || error == ba::error::message_size)
	{
		auto message = boost::make_shared<std::string>(server::make_daytime_string());

		_socket.async_send_to(ba::buffer(*message), _remote_endpoint,
		                      boost::bind(&server::handleSend, this, message,
		                                  ba::placeholders::error,
		                                  ba::placeholders::bytes_transferred));
		std::cout << *message << "size : [" << bytes_transferred << "]" << std::endl;
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
