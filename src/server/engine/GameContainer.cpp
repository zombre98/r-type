/*
** EPITECH PROJECT, 2017
** cpp_indie_studio
** File description:
** Created by armandmgt,
*/

#include "MovementSystem.hpp"
#include "GameContainer.hpp"

ids::GameContainer::GameContainer() : _world{std::make_shared<ecs::World>()} {
	_initSystem();
}

void ids::GameContainer::_initSystem() {
	_listSystem.emplace_back(new ecs::MovementSystem(_world->getEntities()));
}

void ids::GameContainer::runSystem() {
	for (auto &it : _listSystem)
		it->update(1);
}



