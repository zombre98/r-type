//
// Created by Thomas Burgaud on 17/11/2018.
//

#pragma once

#include <string>
#include <vector>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include "../network/protocol.hpp"

namespace net {

	namespace ba = boost::asio;

	class client {
	public:
		explicit client(ba::io_context &context, std::string &address, std::string &port);
		Header getHeaderAndReadBuff();

		template<typename T>
		void sendData(T data) {
			static_assert(std::is_base_of<Package, T>(), "Data you trying to send is not base of Package struct");
			boost::array<T, 1> dataToSend = {{data}};
			_socket.send_to(ba::buffer(dataToSend, sizeof(T)), _senderEndpoint);
		}

		template<typename T>
		T getData() {
			T *pData = reinterpret_cast<T *>(_buff);
			T data(*pData);
			return data;
		}

	private:
		ba::io_context &_ioContext;
		std::string &_address;
		std::string &_port;

		ba::ip::udp::resolver _resolver;
		ba::ip::udp::endpoint _receiverEndpoint;
		ba::ip::udp::endpoint _senderEndpoint;
		ba::ip::udp::socket _socket;
		char _buff[128];
		boost::array<char, 128> _recvArr{};
		std::size_t _bytesReceived;
	};
}