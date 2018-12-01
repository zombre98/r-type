//
// Created by Thomas Burgaud on 30/11/2018.
//

#include <iostream>
#include "InGameBoardSystem.hpp"

ecs::InGameBoardSystem::InGameBoardSystem(ecs::entityVector allEnt, std::shared_ptr<ecs::World> world) :
System{allEnt}, _world{world} {

}

void ecs::InGameBoardSystem::update(double delta[[maybe_unused]]) {
	auto entities = getEntities<Position, ShotType, LifePoint>();

	for (auto &ent : entities) {
		auto  &compPos = ent->getComponent<Position>();
		if (compPos.y < 0 || compPos.x < 0 || compPos.y > 1080 || compPos.x > 1920) {
			ent->getComponent<LifePoint>().lifePoint = 0;
		}
	}
}

