//
// Created by Thomas Burgaud on 14/11/2018.
//

#pragma once

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "server.hpp"
#include "protocol.hpp"

namespace net {
	class protocolServer : public server {
	public:
		protocolServer(ba::io_context &context,unsigned short port);
		void handleData();
		void poll();

		template<typename T>
		void handleSend(const boost::system::error_code &,
		                std::size_t) {

		}

		template<typename T>
		void doReceive(boost::shared_ptr<boost::array<T, 1>>)
		{
		}

		template<typename T>
		void sendData(T data) {
			static_assert(std::is_base_of<Package, T>(), "Data you trying to send is not base of Package struct");
			boost::array<T, 1> newData = {{data}};
			boost::shared_ptr<boost::array<T, 1>> dataToSend = boost::make_shared<boost::array<T, 1>>(newData);
			std::cout << "Address  : [" << _serverEndpoint.address() << " ] Port : [" << _serverEndpoint.port() << "]" << std::endl;
			_socket.async_send_to(ba::buffer(*dataToSend, sizeof(T)), _serverEndpoint,
			                   [this, dataToSend](boost::system::error_code , std::size_t) {
				                   doReceive(dataToSend);
			                   });
		}

		template<typename T>
		void sendDataToAll(T data) {
			std::cout << "New sendDataToAll" << std::endl;
			for (auto &it : _vecPort) {
				_serverEndpoint.port(it);
				sendData<T>(data);
			}
		}
	};
}