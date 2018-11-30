//
// Created by Thomas Burgaud on 22/11/2018.
//

#include <iostream>
#include "SpawnMonsterSystem.hpp"

ecs::SpawnMonsterSystem::SpawnMonsterSystem(ecs::entityVector entities,
			std::shared_ptr<ecs::World> world,
			std::chrono::time_point<std::chrono::steady_clock> ti) :
		System(entities), _world(world), lastSpawn(ti) {
}

void ecs::SpawnMonsterSystem::update(double delta[[maybe_unused]]) {
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<double> diff = now - lastSpawn;
	auto e = getEntities<EnemyType>();
	if (e.size() >= 1)
		return;
	if (diff.count() > 10) {
		lastSpawn = std::chrono::steady_clock::now();
		_world->createEnemies();
	}
}

