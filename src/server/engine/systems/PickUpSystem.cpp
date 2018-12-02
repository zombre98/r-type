//
// Created by Thomas Burgaud on 02/12/2018.
//

#include "PickUpSystem.hpp"

ecs::PickUpSystem::PickUpSystem(ecs::entityVector allEntities, std::shared_ptr<ecs::World> world) : System(allEntities), _world(world) {

}

void ecs::PickUpSystem::update(double delta[[maybe_unused]]) {
	auto entities = getEntities<Player, Position, Hitbox, LifePoint>();
	auto bonus = getEntities<Position, Hitbox, Bonus>();

	for (auto &e : entities) {
		for (auto &bns : bonus) {
			// checking if were are comparing
			// - 2 shots
			// - a player and an ally shot
			// - an enemy and an enemy shot
			/*if (e->hasComponent<ShotType>() ||
			    (e->hasComponent<Player>() &&
			     bns->getComponent<ShotType>().type == ShotType::Shot::ALLY) ||
			    (e->hasComponent<EnemyType>() &&
			     (bns->getComponent<ShotType>().type == ShotType::Shot::ENEMY ||
			      bns->getComponent<ShotType>().type == ShotType::Shot::SHIPENEMY ||
			      bns->getComponent<ShotType>().type == ShotType::Shot::SINUSENEMY)))
				continue;*/

			auto &compPPos = e->getComponent<Position>();
			auto &compPBox = e->getComponent<Hitbox>();
			auto &itemPos = bns->getComponent<Position>();
			auto &itemBox = bns->getComponent<Hitbox>();

			if  ((compPPos.x < itemPos.x + itemBox.width && compPPos.x + compPBox.width > itemPos.x &&
			      compPPos.y < itemPos.y + itemBox.height && compPPos.y + compPBox.height > itemPos.y)) {

				if (bns->getComponent<Bonus>().type == Bonus::Object::LIFE_PACK)
					e->getComponent<LifePoint>().lifePoint += 30;
				bns->getComponent<LifePoint>().lifePoint -= 1;
				e->getComponent<LifePoint>().updated = true;
			}
		}
	}
}
