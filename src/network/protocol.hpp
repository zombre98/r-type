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

	struct Pos {
		Header head;
		int x;
		int y;
	};
}