/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** InputSystem
*/

#include "InputSystem.hpp"

ecs::InputSystem::InputSystem(entityVector allEntities, std::shared_ptr<ecs::World> world)
    : System(allEntities), _world(world)
{}

void ecs::InputSystem::update(double delta[[maybe_unused]]) {
    auto entities = getEntities<Input, Velocity, Position>();

    for (auto &e : entities) {
        auto &input = e->getComponent<Input>();
        auto &velocity = e->getComponent<Velocity>();
        auto &pos = e->getComponent<Position>();

        // dividing booleans by 10 in order to add 0.1 to velocity
        velocity.x += static_cast<float>(input.left) / 10;
        velocity.x += static_cast<float>(input.right) / 10;
        velocity.y += static_cast<float>(input.up) / 10;
        velocity.y += static_cast<float>(input.down) / 10;

        if (input.shoot)
            _world->createShot(Position(pos.x + 10, pos.y));

        input.left = input.right = input.up = input.down = input.shoot = false;
    }
}
