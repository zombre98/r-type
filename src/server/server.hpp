//
// Created by Thomas Burgaud on 12/11/2018.
//

#ifndef R_TYPE_SERVER_HPP
#define R_TYPE_SERVER_HPP

#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace net {
	struct Header {
		int id;
		int op;
	};

	struct pos {
		Header head;
		int x;
		int y;
	};

	namespace ba = boost::asio;
	class server {
	public:
		server(ba::io_context &context,unsigned short port);
		static std::string make_daytime_string();

	private:
		void startReceive();
		void handleReceive(const boost::system::error_code &error,
		                   std::size_t bytes_transferred);
		void handleSend(boost::shared_ptr<std::string> message,
		                 const boost::system::error_code &error,
		                 std::size_t bTransferred);
		template<typename T>
		T getDataFromBuff(char *buff) {
			T *pData = reinterpret_cast<T *>(buff);
			T data = *pData;
			return data;
		}

	private:
		ba::io_context &_ioContext;
		unsigned short _port;
		ba::ip::udp::socket _socket;
		boost::array<char, 128> _recvBuff{};
		ba::ip::udp::endpoint _remote_endpoint;
	};
}

#endif //R_TYPE_SERVER_HPP
