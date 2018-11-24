/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** InputSystem
*/

#include "InputSystem.hpp"

ecs::InputSystem::InputSystem(entityVector allEntities)
    : System(allEntities)
{}

void ecs::InputSystem::update(double delta[[maybe_unused]]) {
    auto entities = getEntities<Input, Velocity>();

    for (auto &e : entities) {
        auto &input e->getComponent<Input>();
        auto &velocity = e->getComponent<Velocity>();

        // dividing booleans by 10 in order to add 0.1 to velocity
        velocity.x += static_cast<float>(input.left) / 10;
        velocity.x += static_cast<float>(input.right) / 10;
        velocity.y += static_cast<float>(input.top) / 10;
        velocity.y += static_cast<float>(input.down) / 10;

        /*
        ** NEED TO MANAGE INPUT SHOOT
        */

        input.left = input.right = input.top = input.down = input.shoot = false;
    }
}
