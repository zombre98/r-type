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
#include "scenes/Scene.hpp"

namespace ba = boost::asio;

class SceneManager;

namespace net {
	class Client {
	public:
		Client(ba::io_context &context, SceneManager &_sceneManager);
		Client(ba::io_context &context, SceneManager &_sceneManager, const std::string &address,
		       const std::string &port);

		void connect(const std::string &address, const std::string &port);
		Header getHeaderAndReadBuff();
		void poll();
		void pollOnce();
		void restart() { _ioContext.restart(); }

		template<typename T>
		void sendData(T data) {
			std::cout << "Send some data" << std::endl;
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
			                      [this, dataToSend](boost::system::error_code, std::size_t) {
				                      afterSend(dataToSend);
			                      });
		}

		template<typename T>
		T getData() {
			T *pData = reinterpret_cast<T *>(_buff);
			return *pData;
		}

		void asyncReceive();

	private:
		template<typename T>
		void afterSend(boost::shared_ptr<boost::array<T, 1>>) {
		}

		template<typename T>
		T getDataFromBuff(char *buff) {
			T *pData = reinterpret_cast<T *>(buff);
			return *pData;
		}

		void receive(const boost::system::error_code &error, std::size_t bytes_transferre);

	public:
		ba::io_context &_ioContext;
//	private:
		SceneManager &_sceneManager;
		std::string _address;
		std::string _port;
		ba::ip::udp::resolver _resolver;
		ba::ip::udp::endpoint _receiverEndpoint;
		ba::ip::udp::endpoint _senderEndpoint;
		ba::ip::udp::socket _socket;
		static int constexpr READ_SIZE = 128;
		char _buff[READ_SIZE];
		boost::array<char, READ_SIZE> _recvArr{};
		std::size_t _bytesReceived;
	};
}
