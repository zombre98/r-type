//
// Created by Thomas Burgaud on 23/11/2018.
//

#include "RemoveSystem.hpp"

ecs::RemoveSystem::RemoveSystem(ecs::entityVector allEntities) : System(allEntities) {
}

void ecs::RemoveSystem::update(double delta[[maybe_unused]]) {
	auto entitiesWithLife = getEntities<ecs::LifePoint>();

	for (auto &entity : entitiesWithLife) {
	}
}
