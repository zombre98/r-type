/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** CollisionSystem
*/

#pragma once

#include "World.hpp"
#include "System.hpp"

namespace ecs {
    class CollisionSystem : public System {
    public:
        CollisionSystem(entityVector, std::shared_ptr<World>);
        ~CollisionSystem() = default;

        void update(double delta) override final;
    private:
        std::shared_ptr<ecs::World> _world;

        bool _collides(const Entity *e, const Entity *shot);
    };
}
