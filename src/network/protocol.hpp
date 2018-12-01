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
		NEW_CONNECTION,
		OLD_CONNECTION,
		NEW_ENEMY,
		NEW_SHOT,
		POSITION,
		INPUT,
		LIFE_POINT,
		DEAD,
		SCORE,
		UNKNOWN_ID,
		LOSE,
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

		NetPlayer(std::size_t id, opCode op, size_t playerId) :
				Package{id, op},
				ecs::Player(playerId) {
		}
	};

	struct Life : Package, ecs::LifePoint, BaseEvent {
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

	struct Dead : Package, ecs::Position, BaseEvent {
		Dead() = delete;

		Dead(std::size_t id, int x, int y, bool m) :
				Package{id, opCode::DEAD},
				ecs::Position{x, y}, isMonster(m) {
		}
		bool isMonster;
	};

	struct Input : Package {
		Input() = delete;

		Input(size_t id, ecs::Input::Action a) :
				Package{id, opCode::INPUT},
				action{a} {
		}

		ecs::Input::Action action;
	};

	struct EnemyType : Package, ecs::EnemyType, BaseEvent {
		EnemyType() = delete;

		EnemyType(std::size_t id, ecs::EnemyType::Enemy t) : Package{id, opCode::NEW_ENEMY}, ecs::EnemyType{t} {}
	};

	struct ShotType : Package, ecs::ShotType, BaseEvent {
		ShotType() = delete;

		ShotType(std::size_t id, ecs::ShotType::Shot s) : Package{id, opCode::NEW_SHOT}, ecs::ShotType{s} {}
	};

	struct UnknownId : Package {
		UnknownId() = delete;

		UnknownId(std::size_t id, std::size_t uId) : Package{id, opCode::UNKNOWN_ID}, id(uId) {}
		std::size_t id;
	};

	struct IsLose : Package {
		IsLose() = delete;

		IsLose(std::size_t id, bool l) : Package{id, opCode::LOSE}, isLose(l) {}
		bool isLose;
	};
}
