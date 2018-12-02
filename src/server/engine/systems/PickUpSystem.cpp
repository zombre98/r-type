//
// Created by Thomas Burgaud on 02/12/2018.
//

#include <iostream>
#include "PickUpSystem.hpp"

namespace ecs {
	PickUpSystem::PickUpSystem(ecs::entityVector allEntities, std::shared_ptr<ecs::World> world) : System(
			allEntities), _world(world) {

	}

	void PickUpSystem::update(double delta[[maybe_unused]]) {
		auto entities = getEntities<Player, Position, Hitbox, LifePoint>();
		auto bonus = getEntities<Position, Hitbox, Bonus>();

		for (auto &e : entities) {
			if (e->getComponent<LifePoint>().lifePoint == 100)
				continue;
			for (auto &bns : bonus) {

				auto &compPPos = e->getComponent<Position>();
				auto &compPBox = e->getComponent<Hitbox>();
				auto &itemPos = bns->getComponent<Position>();
				auto &itemBox = bns->getComponent<Hitbox>();

				if ((compPPos.x < itemPos.x + itemBox.width && compPPos.x + compPBox.width > itemPos.x &&
				     compPPos.y < itemPos.y + itemBox.height && compPPos.y + compPBox.height > itemPos.y)) {

					if (bns->getComponent<Bonus>().type == Bonus::Object::LIFE_PACK) {
						e->getComponent<LifePoint>().lifePoint += 30;
						if (e->getComponent<LifePoint>().lifePoint > 100)
							e->getComponent<LifePoint>().lifePoint = 100;
					}
					bns->getComponent<LifePoint>().lifePoint = 0;
					bns->getComponent<LifePoint>().updated = true;
					e->getComponent<LifePoint>().updated = true;
				}
			}
		}
	}
}
