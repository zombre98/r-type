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
		void getData();
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
			std::cout << "Before sending : " << dataToSend->at(0).x << std::endl;
			_socket.async_send_to(ba::buffer(*dataToSend), _remote_endpoint,
			                   [this, dataToSend](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/) {
				                   doReceive(dataToSend);
			                   });
		}
	};
}