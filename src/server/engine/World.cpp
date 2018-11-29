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

ecs::Entity &ecs::World::createPlayer() {
	static std::size_t idPlayer = 0;
	auto &ent = createEntity();

	//	std::cout << "[" << ent.id << "]" << " : New Player" << std::endl;
	ent.addComponent<Player>(idPlayer++);
	ent.addComponent<LifePoint>(100);
	ent.addComponent<Position>(std::rand() % 1000, std::rand() % 1000);
	ent.addComponent<Velocity>(0, 0);
	ent.addComponent<Score>(0);
	ent.addComponent<Input>();
	return ent;
}

void ecs::World::createEnemies() {
	auto &ent = createEntity();

	std::cout << "[" << ent.id << "]" << " : New enemy" << std::endl;
	ent.addComponent<Position>(1950, std::rand() % 1080);
	ent.addComponent<LifePoint>(10);
	ent.addComponent<EnemyType>(EnemyType::Enemy::CLASSIC);
	ent.addComponent<Velocity>(-1, 0);
}

void ecs::World::createAllyShot(const Position &pos) {
    auto &ent = createEntity();

    ent.addComponent<Position>(pos.x, pos.y);
	ent.addComponent<Velocity>(0, 3);
    ent.addComponent<Damage>(30);
    ent.addComponent<ShotType>(ShotType::Shot::ALLY);
}
