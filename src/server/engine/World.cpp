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
	ent.addComponent<Hitbox>(33, 17);
	ent.addComponent<Score>(0);
	ent.addComponent<Input>();
	return ent;
}


void ecs::World::createClassicEnemies() {
	auto &ent = createEntity();

	ent.addComponent<Position>(1950, std::rand() % 1080);
	ent.addComponent<LifePoint>(90);
	ent.addComponent<EnemyType>(EnemyType::Enemy::CLASSIC);
	ent.addComponent<Hitbox>(33, 34);
	ent.addComponent<Velocity>(-1, 0);
}

void ecs::World::createShot(const Position &pos, ShotType::Shot sType) {
    auto &ent = createEntity();

    ent.addComponent<Position>(pos.x, pos.y);
	ent.addComponent<Velocity>(0, 3);
	if (sType == ShotType::Shot::ENEMY) {
	    ent.addComponent<Damage>(30);
	    ent.addComponent<Hitbox>(18, 16);
	} else if (sType == ShotType::Shot::SHIPENEMY) {
		ent.addComponent<Damage>(50);
		ent.addComponent<Hitbox>(15, 16);
	} else if (sType == ShotType::Shot::ALLY) {
		ent.addComponent<Damage>(30);
		ent.addComponent<Hitbox>(18, 16);
	}
    ent.addComponent<LifePoint>(1);
    ent.addComponent<ShotType>(sType);
}

void ecs::World::createCustomShot(const Position &pos, const Velocity &v,
                                  const Hitbox &hbox, ShotType::Shot sType,
                                  int damage) {
    auto &ent = createEntity();

    ent.addComponent<Velocity>(v.x, v.y);
    ent.addComponent<Position>(pos.x, pos.y);
    ent.addComponent<Hitbox>(hbox.width, hbox.height);
    ent.addComponent<Damage>(damage);
    ent.addComponent<LifePoint>(1);
    ent.addComponent<ShotType>(sType);
}

void ecs::World::createShipEnemy() {
	auto &ent = createEntity();

	ent.addComponent<Position>(1950, 1080);
	ent.addComponent<LifePoint>(150);
	ent.addComponent<EnemyType>(EnemyType::Enemy::SHIP);
	ent.addComponent<Hitbox>(66, 50);
	ent.addComponent<Velocity>(-1, 0);
}

void ecs::World::createSinusEnemy() {
	auto &ent = createEntity();

	ent.addComponent<Position>(1950, std::rand() % 1080);
	ent.addComponent<LifePoint>(50);
	ent.addComponent<EnemyType>(EnemyType::Enemy::SINUS);
	ent.addComponent<Hitbox>(27, 27);
	ent.addComponent<Velocity>(-5, 0);
}

void ecs::World::createUselessEnemy() {
	auto &ent = createEntity();

	ent.addComponent<Position>(1950, -300);
	ent.addComponent<LifePoint>(90);
	ent.addComponent<EnemyType>(EnemyType::Enemy::CLASSIC);
	ent.addComponent<Hitbox>(33, 34);
	ent.addComponent<Velocity>(-1, 0);
}

bool ecs::World::isLoose() {
	auto const &ent = getEntities<Player>();
	return ent.empty();
}

bool ecs::World::isEmpty() {
	auto const &ent = getAllEntities();
	return ent->size() <= 1;
}
