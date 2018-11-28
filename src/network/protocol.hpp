//
// Created by Thomas Burgaud on 14/11/2018.
//

#pragma once

#include "Components.hpp"
#include "Entity.hpp"
#include "events/EventManager.hpp"

namespace net {
	enum class opCode {
		NO_OP,
		CONNECTION,
		OLD_CONNECTION,
		POSITION,
		INPUT,
		LIFE_POINT,
		DEAD,
		SCORE,
		NEW_STAGE,
		SPRITE_STAGE,
		STAGE_IS_WIN
	};

	struct Header {
		Header() = default;

		Header(std::size_t i, opCode o) :
			id(i),
			op(o) {
		}
		std::size_t id;
		opCode op;
	};

	struct Package {
		Package() = delete;
		explicit Package(Header &head) : head(head) {}

		Package(std::size_t id, opCode op) :
			head(id, op) {
		}
		Header head;
	};

	struct Pos : Package, ecs::Position, BaseEvent {
		Pos() = delete;

		Pos(std::size_t _id, opCode op, int x, int y) :
			Package{_id, op},
			ecs::Position(x, y) {
		}
	};

	struct NetPlayer : Package, ecs::Player, BaseEvent {
		NetPlayer() = delete;

		NetPlayer(std::size_t id, opCode op) :
			Package{id, op},
			ecs::Player(id) {
		}
	};

	struct Life : Package, ecs::LifePoint {
		Life() = delete;

		Life(std::size_t id, int life) :
			Package{id, opCode::LIFE_POINT},
			ecs::LifePoint(life) {
		}
	};

	struct Score : Package, ecs::Score {
		Score() = delete;

		Score(std::size_t id, int score) :
			Package{id, opCode::SCORE},
			ecs::Score{score} {
		}
	};

	struct Dead : Package, ecs::Position {
		Dead() = delete;

		Dead(std::size_t id, int x, int y) :
			Package{id, opCode::POSITION},
			ecs::Position{x, y} {
		}
	};

	struct Input : Package {
		Input() = delete;

		Input(size_t id, ecs::Input::Action a) :
			Package{id, opCode::INPUT},
			action{a} {
		}

		ecs::Input::Action action;
	};
}
