#include <utility>

//
// Created by Thomas Burgaud on 12/11/2018.
//

#pragma once

#include <string>
#include <unordered_set>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "address.hpp"

namespace net {
	namespace ba = boost::asio;

	class Server {
	public:
		Server(ba::io_context &context,unsigned short port);

	public:
		void startReceive();
		void receive(const boost::system::error_code &error, std::size_t bytes_transferred);


		template<typename T>
		T getDataFromBuff(char *buff) {
			T *pData = reinterpret_cast<T *>(buff);
			T data(*pData);
			return data;
		}

	protected:
		ba::io_context &_ioContext;
		unsigned short _port;
		ba::ip::udp::endpoint _serverEndpoint;
		ba::ip::udp::socket _socket;
		std::size_t _bytesToRead;
		char _buff[128];
		std::unordered_set<Address> _setClient;
		boost::array<char, 128> _recvArr{};
	};
}
