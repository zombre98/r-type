//
// Created by Thomas Burgaud on 22/11/2018.
//

#include "SpawnMonster.hpp"

ecs::SpawnMonster::SpawnMonster(ecs::entityVector entities, std::shared_ptr<ecs::World> world, std::chrono::time_point<std::chrono::steady_clock> ti) :
System(entities), _world(world), lastSpawn(ti) {
}

void ecs::SpawnMonster::update(double delta[[maybe_unused]]) {
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<double> diff = now - lastSpawn;
	if (diff.count() > 10) {
		lastSpawn = std::chrono::steady_clock::now();
		_world->createEnemies();
	}
}

