/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MovementSystem
*/

#include "MovementShootSystem.hpp"

namespace ecs {
	MovementShootSystem::MovementShootSystem(entityVector allEntities, std::chrono::time_point<std::chrono::steady_clock> ti) :
			System(allEntities), _lastMove(ti) {
	}

	void MovementShootSystem::update(double delta[[maybe_unused]]) {
		auto entities = getEntities<ShotType, Velocity>();
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = now - _lastMove;

		if (diff.count() > 0.05) {
			for (auto &e : entities) {
				if (e->getComponent<ShotType>().type == ShotType::Shot::ALLY)
					e->getComponent<Velocity>().x = 7;
			}
			_lastMove = std::chrono::steady_clock::now();
		}
	}
};
