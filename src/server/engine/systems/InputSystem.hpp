/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** InputSystem
*/

#pragma once

#include "System.hpp"

namespace ecs {
    class InputSystem : public System {
        InputSystem(entityVector);
        ~InputSystem = default;

        void update(double delta) override final;
    };
}
