//
// Created by Thomas Burgaud on 14/11/2018.
//

#pragma once

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "Server.hpp"
#include "GameContainer.hpp"
#include "protocol.hpp"

namespace net {
	class ProtocolServer : public Server {
	public:
		ProtocolServer(ba::io_context &context,unsigned short port);
		void handleData();
		void poll();

		template<typename T>
		void handleSend(const boost::system::error_code &, std::size_t) {

		}

		template<typename T>
		void doReceive(boost::shared_ptr<boost::array<T, 1>>) {
		}

		template<typename T>
		void sendDataTo(T data, Address const &addr) {
			_serverEndpoint.port(addr.port);
			sendData(data);
		}

		template<typename T>
		void sendData(T data) {
			static_assert(std::is_base_of<Package, T>(), "Data is not a base of Package");
			boost::array<T, 1> newData = {{data}};
			auto dataToSend = boost::make_shared<boost::array<T, 1>>(newData);
			_socket.async_send_to(ba::buffer(*dataToSend, sizeof(T)), _serverEndpoint,
			                   [this, dataToSend](boost::system::error_code , std::size_t) {
				                   doReceive(dataToSend);
			                   });
		}

		template<typename T>
		void sendDataToAll(T data) {
			for (auto &it : _setClient) {
				_serverEndpoint.port(it.port);
				sendData<T>(data);
			}
		}

	private:
		void _sendScore();
		void _sendDeadEntities();
		void _sendLifePoint();
		void _sendAllPosition();
		void _handleNewClient();
	private:
		rtype::GameContainer _gContainer{};
	};
}
