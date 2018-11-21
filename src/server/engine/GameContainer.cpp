/*
** EPITECH PROJECT, 2017
** cpp_indie_studio
** File description:
** Created by armandmgt,
*/

#include "MovementSystem.hpp"
#include "GameContainer.hpp"

rtype::GameContainer::GameContainer() : _world{std::make_shared<ecs::World>()} {
	_initSystem();
}

void rtype::GameContainer::_initSystem() {
	_listSystem.emplace_back(new ecs::MovementSystem(_world->getEntities()));
}

void rtype::GameContainer::runSystem() {
	for (auto &it : _listSystem)
		it->update(1);
}



