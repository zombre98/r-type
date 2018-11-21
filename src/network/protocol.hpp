//
// Created by Thomas Burgaud on 14/11/2018.
//

#pragma once

#include "Components.hpp"

namespace net {
	enum class protocolRType {
		PLAYER_POSITION,
		CONNECTION,
		INPUT,
		ENEMIES_POSITION,
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
		Pos(Header &head, int x, int y) : Package{head}, ecs::Position(x, y) {}
	};

	struct netPlayer : Package, ecs::Player {
		netPlayer() = default;
		netPlayer(std::size_t id, protocolRType op) : Package{id, op}, ecs::Player(id) {};
	};
}
