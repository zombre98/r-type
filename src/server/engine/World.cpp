//
// Created by Thomas Burgaud on 21/11/2018.
//

#include <iostream>
#include "World.hpp"

ecs::Entity &ecs::World::createEntity() {
	entities->emplace_back(std::make_unique<Entity>());
	return *entities->back();
}

void ecs::World::eraseEntity(std::size_t const &id) {
	auto entity = std::find_if(entities->begin(), entities->end(), [id] (const std::unique_ptr<Entity> &e) {
		return e->id == id;
	});
	entities->erase(entity);
}

void ecs::World::createPlayer() {
	static std::size_t idPlayer = 0;
	auto &ent = createEntity();

	ent.addComponent<Player>(idPlayer++);
	ent.addComponent<LifePoint>(100);
	ent.addComponent<Position>(std::rand() % 100, std::rand() % 100);
	ent.addComponent<Score>(0);
}

void ecs::World::createEnemies() {
	auto &ent = createEntity();

	ent.addComponent<Position>(std::rand() % 100, std::rand() % 100);
	ent.addComponent<LifePoint>(10);
}

