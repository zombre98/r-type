//
// Created by Thomas Burgaud on 14/11/2018.
//

#pragma once

namespace net {
	enum class protocolRType {
		PLAYER_POSITION,
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
		int id;
		protocolRType op;
	};

	struct Package {
		Package() = default;
		explicit Package(Header &head) : head(head) {}
		Header head;
	};

	struct Pos : Package {
		Pos() = default;
		Pos(Header &head, int x, int y) : Package{head}, x{x}, y{y} {}
		int x;
		int y;
	};
}