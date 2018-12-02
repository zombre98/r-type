/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** InputSystem
*/

#include <iostream>
#include "CollisionSystem.hpp"

ecs::CollisionSystem::CollisionSystem(entityVector allEntities,
                                      std::shared_ptr<ecs::World> world)
    : System(allEntities), _world(world)
{}

void ecs::CollisionSystem::update(double delta[[maybe_unused]]) {
    auto entities = getEntities<Velocity, Position, Hitbox, LifePoint>();
    auto shots = getEntities<Position, Hitbox, ShotType, Damage>();

    for (auto &e : entities) {
        for (auto &s : shots) {
            // checking if were are comparing
            // - 2 shots
            // - a player and an ally shot
            // - an enemy and an enemy shot
            if (e->hasComponent<ShotType>() ||
                (e->hasComponent<Player>() &&
                 s->getComponent<ShotType>().type == ShotType::Shot::ALLY) ||
                (e->hasComponent<EnemyType>() &&
                 (s->getComponent<ShotType>().type == ShotType::Shot::ENEMY ||
                  s->getComponent<ShotType>().type == ShotType::Shot::SHIPENEMY ||
                  s->getComponent<ShotType>().type == ShotType::Shot::SINUSENEMY)))
                continue;

            auto &compPPos = e->getComponent<Position>();
	        auto &compPBox = e->getComponent<Hitbox>();
	        auto &compShotPos = s->getComponent<Position>();
	        auto &compShotBox = s->getComponent<Hitbox>();

	        if  ((compPPos.x < compShotPos.x + compShotBox.width && compPPos.x + compPBox.width > compShotPos.x &&
	             compPPos.y < compShotPos.y + compShotBox.height && compPPos.y + compPBox.height > compShotPos.y)) {

		        e->getComponent<LifePoint>().lifePoint -= s->getComponent<Damage>().damage;
		        s->getComponent<LifePoint>().lifePoint -= 1;
		        e->getComponent<LifePoint>().updated = true;
	        }
        }
    }
}
