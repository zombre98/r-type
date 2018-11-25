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
        InputSystem(entityVector);

        void update(double delta) override final;

    private:
        std::shared_ptr<ecs::World> _world;
    };
}
