//
// Created by Thomas Burgaud on 12/11/2018.
//

#pragma once

#include <string>
#include <vector>
#include <queue>
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
		T getDataFromBuff() {
			T *pData = reinterpret_cast<T *>(_buff.front().elems);
			_buff.pop();
			return *pData;
		}

	protected:
		using message = boost::array<char, 128>;

		ba::io_context &_ioContext;
		unsigned short _port;
		ba::ip::udp::endpoint _serverEndpoint;
		ba::ip::udp::socket _socket;
		std::vector<Address> _setClient;
		message _recvArr{};
		std::queue<message> _buff;
	};
}
