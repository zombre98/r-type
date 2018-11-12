//
// Created by Thomas Burgaud on 12/11/2018.
//

#ifndef R_TYPE_SERVER_HPP
#define R_TYPE_SERVER_HPP

#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace net {
	class server {
	public:
		server(boost::asio::io_context &context,unsigned short port);
		static std::string make_daytime_string();

	private:
		void startReceive();
		void handleReceive(const boost::system::error_code &error,
		                   std::size_t bytes_transferred);
		void handleSend(boost::shared_ptr<std::string> message,
		                 const boost::system::error_code &error,
		                 std::size_t bTransferred);


	private:
		boost::asio::io_context &_ioContext;
		unsigned short _port;
		boost::asio::ip::udp::socket _socket;
		boost::array<char, 1> _recv_buff;
		boost::asio::ip::udp::endpoint _remote_endpoint;
	};
}

#endif //R_TYPE_SERVER_HPP
