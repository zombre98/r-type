//
// Created by Thomas Burgaud on 14/11/2018.
//

#pragma once

#include "Components.hpp"
#include "Entity.hpp"

namespace net {
	enum class protocolRType {
		CONNECTION,
		OlD_CONNECTION,
		POSITION,
		INPUT,
		SHOOT,
		LIFE_POINT,
		DEAD,
		SCORE,
		NEW_STAGE,
		SPRITE_STAGE,
		STAGE_IS_WIN
	};

	struct Header {
		Header() = default;
		Header(std::size_t i, protocolRType o) : id(i), op(o) {}
		std::size_t id;
		protocolRType op;
	};

	struct Package {
		Package() = default;
		explicit Package(Header &head) : head(head) {}
		Package(std::size_t id, protocolRType op) : head(id, op) {}
		Header head;
	};

	struct Pos : Package, ecs::Position {
		Pos() = default;
		Pos(std::size_t _id, protocolRType op, int x, int y) : Package{_id, op}, ecs::Position(x, y) {}
	};

	struct NetPlayer : Package, ecs::Player {
		NetPlayer() = default;
		NetPlayer(std::size_t id, protocolRType op) : Package{id, op}, ecs::Player(id) {}
	};

	struct Life : Package, ecs::LifePoint {
		Life() = default;
		Life(std::size_t id, protocolRType op, int life) : Package{id, op}, ecs::LifePoint(life) {}
	};
}
