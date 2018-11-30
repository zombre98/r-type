//
// Created by Thomas Burgaud on 30/11/2018.
//
#include <iostream>
#include "EnemiesShootSystem.hpp"

namespace ecs {
	EnemiesShootSystem::EnemiesShootSystem(entityVector allEntities, std::shared_ptr<World> w, std::chrono::time_point<std::chrono::steady_clock> ti) :
			System(allEntities), _world(w), _lastShoot(ti) {
	}

	void EnemiesShootSystem::update(double delta[[maybe_unused]]) {
		auto entities = getEntities<EnemyType, Position>();
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = now - _lastShoot;

		if (entities.empty()) {
			return;
		}
		if (diff.count() > 2.0) {
			for (auto &e : entities) {
				if (e->getComponent<EnemyType>().type == EnemyType::Enemy::CLASSIC) {
					_world->createShot(e->getComponent<Position>(), ShotType::Shot::ENEMY);
				}
			}
			_lastShoot = std::chrono::steady_clock::now();
		}
	}
};
