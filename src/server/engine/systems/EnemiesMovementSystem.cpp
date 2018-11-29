/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MovementSystem
*/

#include "EnemiesMovementSystem.hpp"

namespace ecs {
	EnemiesMovementSystem::EnemiesMovementSystem(entityVector allEntities, std::chrono::time_point<std::chrono::steady_clock> ti) :
			System(allEntities), _lastMove(ti) {
	}

	void EnemiesMovementSystem::update(double delta[[maybe_unused]]) {
		auto entities = getEntities<EnemyType, Velocity>();
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = now - _lastMove;

		if (diff.count() > 0.5) {
			for (auto &e : entities) {
				if (e->getComponent<EnemyType>().type == EnemyType::Enemy::CLASSIC)
					e->getComponent<Velocity>().x = -7;
			}
			_lastMove = std::chrono::steady_clock::now();
		}
	}
};
