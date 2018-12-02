//
// Created by Thomas Burgaud on 23/11/2018.
//

#include "RemoveSystem.hpp"

ecs::RemoveSystem::RemoveSystem(ecs::entityVector allEntities, std::shared_ptr<ecs::World> world) :
System(allEntities),  _world{world} {
}

void ecs::RemoveSystem::update(double delta[[maybe_unused]]) {
	auto entitiesWithLife = getEntities<ecs::LifePoint>();

	for (auto &entity : entitiesWithLife) {
		if (entity->getComponent<ecs::LifePoint>().lifePoint <= 0) {
			if (entity->hasComponent<ScoreEnemy>()) {
				auto check = getEntities<Score>();
				if (check.empty())
					_world->createScore();
				auto scores = getEntities<Score>();
				for (auto score : scores) {
					score->getComponent<Score>().score += entity->getComponent<ScoreEnemy>().enemyValue;
					score->getComponent<Score>().updated = true;
				}
			}
			if (entity->hasComponent<Destructible>()) {
				auto type = entity->getComponent<Destructible>().type;
				auto pos = entity->getComponent<Position>();
				_world->createBonus(type, pos);
			}
			_world->eraseEntity(entity->id);
		}
	}
}
