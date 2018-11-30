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
    auto entities = getEntities<Velocity, Position, Hitbox, LifePoint, EnemyType>();
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
                 s->getComponent<ShotType>().type == ShotType::Shot::ENEMY))
                continue;

            auto &compPPos = e->getComponent<Position>();
	        auto &compPBox = e->getComponent<Hitbox>();
	        auto &compShotPos = s->getComponent<Position>();
	        auto &compShotBox = s->getComponent<Hitbox>();
	        std::cout << (compPPos.x < compShotPos.x + compShotBox.width);
	        std::cout << (compPPos.x + compPBox.width > compShotPos.x);
	        std::cout << (compPPos.y > compShotPos.y + compShotBox.height);
	        std::cout << (compPPos.y + compPBox.height < compShotPos.y) << std::endl;

	        std::cout << "c1 : " << compPPos.x << " < " << compShotPos.x + compShotBox.width << std::endl;
	        std::cout << "c2 : " << compPPos.x + compPBox.width << " > " << compShotPos.x << std::endl;
	        std::cout << "c3 : " << compPPos.y << " > " << compShotPos.y + compShotBox.height << std::endl;
	        std::cout << "c4 : " << compPPos.y + compPBox.height << " < " << compShotPos.y << std::endl;
	        if  ((compPPos.x < compShotPos.x + compShotBox.width && compPPos.x + compPBox.width > compShotPos.x &&
	             compPPos.y > compShotPos.y + compShotBox.height && compPPos.y + compPBox.height < compShotPos.y)) {


		        std::cout << "Shot hitbox : " << compPBox.height << ", " << compPBox.width << std::endl;
		        std::cout << "Pos shoot : " << compShotPos.x << ", " << compShotPos.y << std::endl;
		        std::cout << "Enely hitbox : " << compShotBox.height << ", " << compShotBox.width << std::endl;
		        std::cout << "Pos Enemy : " << compPPos.x << ", " << compPPos.y << std::endl;
		        std::cout << "Collide" << std::endl;
		        e->getComponent<LifePoint>().lifePoint -= s->getComponent<Damage>().damage;
		        s->getComponent<LifePoint>().lifePoint -= 1;
	        }
        }
    }
}
