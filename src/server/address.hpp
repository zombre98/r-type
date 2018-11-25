//
// Created by Thomas Burgaud on 19/11/2018.
//

#pragma once

#include <boost/asio.hpp>

namespace net {

	namespace ba = boost::asio;

	struct Address {
	public:
		Address(ba::ip::address addr, unsigned short prt) : address{std::move(addr)}, port{prt}, id{_nextId++} {}

		bool operator==(Address const &rvalue) const {
			return rvalue.getId() == id;
		}

		std::size_t getId() const { return id; }

	public:
		ba::ip::address address;
		unsigned short port;
		std::size_t id;
		static std::size_t _nextId;
	};
}

namespace std
{
	template<>
	struct hash<net::Address>
	{
		size_t operator()(net::Address const &addr) const {
			return hash<size_t >()(addr.getId());
		}
	};
}