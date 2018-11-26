/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MovementSystem
*/

#include <iostream>
#include "vec.hpp"
#include "MovementSystem.hpp"

namespace ecs {
	MovementSystem::MovementSystem(entityVector allEntities)
			: System(allEntities)
	{
	}

	bool MovementSystem::_isValidPosition(float x, float y) {
		auto entities = getEntities<Position>();

		for (auto &entity : entities) {
				auto &posE = entity->getComponent<Position>();
				auto posP = roundPos<int>(x, y);
				auto posRounded = roundPos<int>(posE.x, posE.y);
				if (posP == posRounded)
					return false;
		}
		return true;
	}

	void MovementSystem::update(double delta[[maybe_unused]]) {
		auto entities = getEntities<Position, Velocity>();

		for (auto &entity : entities) {
			auto &position = entity->getComponent<Position>();
			auto &velocity = entity->getComponent<Velocity>();
			if (velocity.x == 0.0f && velocity.y == 0.0f) {
				continue;
			}
			if (_isValidPosition(position.x + velocity.x, position.y))
				position.x += velocity.x;
			if (_isValidPosition(position.x, position.y + velocity.y))
				position.y += velocity.y;
			velocity.x = 0;
			velocity.y = 0;
		}
	}
};
