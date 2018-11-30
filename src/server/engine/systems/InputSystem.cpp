/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** InputSystem
*/

#include <utility>
#include <iostream>
#include "InputSystem.hpp"

ecs::InputSystem::InputSystem(entityVector allEntities, std::shared_ptr<ecs::World> world) :
	System(allEntities),
	_world(world)
{}

void ecs::InputSystem::update(double delta[[maybe_unused]]) {
	auto entities = getEntities<Input, Position, Velocity>();

    for (auto &e : entities) {
	    auto &inputComp = e->getComponent<Input>();
	    updateVelocity(e, inputComp);
	    doShoot(e, inputComp);
	    inputComp.input.reset();
    }
}

void ecs::InputSystem::updateVelocity(ecs::Entity *e, const ecs::Input &inputComp) {
	auto &velocity = e->getComponent<Velocity>();
	velocity.x -= static_cast<int>(inputComp.input[ecs::Input::Left]) * 15;
	velocity.x += static_cast<int>(inputComp.input[ecs::Input::Right]) * 15;
	velocity.y -= static_cast<int>(inputComp.input[ecs::Input::Up]) * 15;
	velocity.y += static_cast<int>(inputComp.input[ecs::Input::Down]) * 15;
}

void ecs::InputSystem::doShoot(ecs::Entity *e, const ecs::Input &inputComp) {
	if (inputComp.input[ecs::Input::Shoot]) {
		auto &pos = e->getComponent<Position>();
		_world->createAllyShot(Position(pos.x + 10, pos.y));
	}
}
