//
// Created by Thomas Burgaud on 23/11/2018.
//

#include "RemoveSystem.hpp"

ecs::RemoveSystem::RemoveSystem(ecs::entityVector allEntities, ecs::World &world) :
System(allEntities),  _world{world} {
}

void ecs::RemoveSystem::update(double delta[[maybe_unused]]) {
	auto entitiesWithLife = getEntities<ecs::LifePoint>();

	for (auto &entity : entitiesWithLife) {
		if (entity->getComponent<ecs::LifePoint>().lifePoint <= 0) {
			_world.eraseEntity(entity->id);
		}
	}
}
