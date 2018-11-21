//
// Created by Thomas Burgaud on 21/11/2018.
//

#include "World.hpp"

ecs::Entity &ecs::World::createEntity() {
	entities->emplace_back(std::make_unique<Entity>());
	return *entities->back();
}
