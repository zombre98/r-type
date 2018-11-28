/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** InputSystem
*/

#include <utility>
#include "InputSystem.hpp"

ecs::InputSystem::InputSystem(entityVector allEntities, std::shared_ptr<ecs::World> world) :
	System(std::move(allEntities)),
	_world(std::move(world))
{}

void ecs::InputSystem::update(double delta[[maybe_unused]]) {
	auto entities = getEntities<Input>();

    for (auto &e : entities) {
	    auto &inputComp = e->getComponent<Input>();
	    if (e->hasComponent<Velocity>())
		    updateVelocity(e, inputComp);
	    if (e->hasComponent<Position>())
		    doShoot(e, inputComp);
	    inputComp.input.reset();
    }
}

void ecs::InputSystem::updateVelocity(ecs::Entity *e, const ecs::Input &inputComp) {
	auto &velocity = e->getComponent<Velocity>();
	// dividing booleans by 10 in order to add 0.1 to velocity
	velocity.x += static_cast<float>(inputComp.input[ecs::Input::Left]) / 10;
	velocity.x += static_cast<float>(inputComp.input[ecs::Input::Right]) / 10;
	velocity.y += static_cast<float>(inputComp.input[ecs::Input::Up]) / 10;
	velocity.y += static_cast<float>(inputComp.input[ecs::Input::Down]) / 10;
	//        std::cout << inputComp.input[ecs::Input::Left] << inputComp.input[ecs::Input::Right] << inputComp.input[ecs::Input::Up] << inputComp.input[ecs::Input::Down] << std::endl;
	//        std::cout << velocity.x << velocity.x << velocity.y << velocity.y << std::endl;
}

void ecs::InputSystem::doShoot(ecs::Entity *e, const ecs::Input &inputComp) {
	if (inputComp.input[ecs::Input::Shoot]) {
		auto &pos = e->getComponent<Position>();
		_world->createAllyShot(Position(pos.x + 10, pos.y));
	}
}
