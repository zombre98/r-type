/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** InputSystem
*/

#pragma once

#include "World.hpp"
#include "System.hpp"

namespace ecs {
    class InputSystem : public System {
    public:
        InputSystem(entityVector, std::shared_ptr<World>);

        void update(double delta) override final;

    private:
        std::shared_ptr<ecs::World> _world;
	    void updateVelocity(Entity *e, const Input &inputComp);
	    void doShoot(Entity *e, const Input &inputComp);
    };
}
