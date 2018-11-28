/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** InputSystem
*/

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
                 s->getComponent<ShotType>().type == ShotType::Shot::ENEMY))
                continue;
            if (!_collides(e, s))
                continue;
            e->getComponent<LifePoint>().lifePoint -= s->getComponent<Damage>().damage;
            _world->eraseEntity(s->id);
        }
    }
}

bool ecs::CollisionSystem::_collides(const Entity *e, const Entity *shot) {
    auto &ePos = e->getComponent<Position>();
    auto &eBox = e->getComponent<Hitbox>();
    auto &shotPos = shot->getComponent<Position>();
    auto &shotBox = shot->getComponent<Hitbox>();

    // (RectA.Left < RectB.Right && RectA.Right > RectB.Left &&
    //  RectA.Top > RectB.Bottom && RectA.Bottom < RectB.Top )
    // = colliding
    if (ePos.x < shotPos.x + shotBox.width && ePos.x + eBox.width > shotPos.x &&
        ePos.y > shotPos.y + shotBox.height && ePos.y + eBox.height < shotPos.y)
        return (true);
    return (false);
}
