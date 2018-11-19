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
#include "protocol.hpp"

namespace net {

	namespace ba = boost::asio;

	class Client {
	public:
		explicit Client(ba::io_context &context, std::string &address, std::string &port);
		Header getHeaderAndReadBuff();
		void poll();

		template<typename T>
		void sendData(T data) {
			static_assert(std::is_base_of<Package, T>(), "Data is not a base of Package");
			boost::array<T, 1> dataToSend = {{data}};
			_socket.send_to(ba::buffer(dataToSend, sizeof(T)), _senderEndpoint);
		}

		template<typename T>
		void asyncSendData(T data) {
			static_assert(std::is_base_of<Package, T>(), "Data is not a base of Package");
			boost::array<T, 1> newData = {{data}};
			auto dataToSend = boost::make_shared<boost::array<T, 1>>(newData);
			_socket.async_send_to(ba::buffer(*dataToSend, sizeof(T)), _senderEndpoint,
			                      [this, dataToSend](boost::system::error_code , std::size_t) {
									afterSend(dataToSend);
			                      });
		}

		template<typename T>
		T getData() {
			T *pData = reinterpret_cast<T *>(_buff);
			T data(*pData);
			return data;
		}

		void asyncReceive();

	private:
		template<typename T>
		void afterSend(boost::shared_ptr<boost::array<T, 1>> data) {

		}

		template<typename T>
		T getDataFromBuff(char *buff) {
			T *pData = reinterpret_cast<T *>(buff);
			return *pData;
		}

		void receive(const boost::system::error_code &error, std::size_t bytes_transferre);

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
