//
// Created by Thomas Burgaud on 22/11/2018.
//

#include <iostream>
#include "SpawnMonsterSystem.hpp"

ecs::SpawnMonsterSystem::SpawnMonsterSystem(ecs::entityVector entities,
			std::shared_ptr<ecs::World> world,
			std::chrono::time_point<std::chrono::steady_clock> ti) :
    System(entities), _world(world), lastClassicSpawn(ti), lastShipSpawn(ti), lastSinusSpawn(ti) {
}

void ecs::SpawnMonsterSystem::update(double delta[[maybe_unused]]) {
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<double> diffClassic = now - lastClassicSpawn;
	std::chrono::duration<double> diffShip = now - lastShipSpawn;
        std::chrono::duration<double> diffSinus = now - lastSinusSpawn;


	if (diffClassic.count() > 10) {
		lastClassicSpawn = std::chrono::steady_clock::now();
		_world->createClassicEnemies();
	}
	if (diffShip.count() > 20) {
		lastShipSpawn = std::chrono::steady_clock::now();
		_world->createShipEnemy();
	}
        if (diffSinus.count() > 5) {
		lastSinusSpawn = std::chrono::steady_clock::now();
		_world->createSinusEnemy();
	}
}
