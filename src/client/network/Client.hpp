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
#include <queue>
#include "protocol.hpp"
#include "scenes/Scene.hpp"

namespace ba = boost::asio;

class SceneManager;

namespace net {
	class Client {
	public:
		Client(ba::io_context &context, SceneManager &_sceneManager);

		void connect(const std::string &address, const std::string &port);

		bool isConnected() const noexcept {
			return _connected;
		}
		void poll();

		void restart() { _ioContext.restart(); }

		template<typename T>
		void sendData(T data) {
			static_assert(std::is_base_of<Package, T>(), "Data is not a base of Package");
			//			std::cout << "Sending data" << std::endl;
			data.head.id = _me;
			boost::array<T, 1> dataToSend = {{data}};
			_socket.send_to(ba::buffer(dataToSend, sizeof(T)), _senderEndpoint);
		}

		virtual ~Client();

		template<typename T>
		void asyncSendData(T data) {
			static_assert(std::is_base_of<Package, T>(), "Data is not a base of Package");
			data.head.id = _me;
			boost::array<T, 1> newData = {{data}};
			auto dataToSend = boost::make_shared<boost::array<T, 1>>(newData);
			_socket.async_send_to(ba::buffer(*dataToSend, sizeof(T)), _senderEndpoint,
			                      [this, dataToSend](boost::system::error_code, std::size_t) {
				                      afterSend(dataToSend);
			                      });
		}

		template<typename T>
		T getData() {
			T *pData = reinterpret_cast<T *>(_buff.front().elems);
			return *pData;
		}

		void asyncReceive();

		std::size_t getId() { return _me; }

	private:
		template<typename T>
		void afterSend(boost::shared_ptr<boost::array<T, 1>>) {
		}

		void receive(const boost::system::error_code &error, std::size_t bytes_transferred);
		void handleMessage();

	private:
		using message = boost::array<char, 128>;

		ba::io_context &_ioContext;
		SceneManager &_sceneManager;
		std::string _address;
		std::string _port;
		ba::ip::udp::resolver _resolver;
		ba::ip::udp::endpoint _receiverEndpoint;
		ba::ip::udp::endpoint _senderEndpoint;
		ba::ip::udp::socket _socket;
		message _recvArr{};
		std::queue<message> _buff;
		size_t _me;
		bool _connected{false};
		bool _connecting{false};
		std::thread _connectionTimeout{};
	};
}
