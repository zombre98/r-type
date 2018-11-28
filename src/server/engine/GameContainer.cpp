/*
** EPITECH PROJECT, 2017
** cpp_indie_studio
** File description:
** Created by armandmgt,
*/

#include "InputSystem.hpp"
#include "MovementSystem.hpp"
#include "RemoveSystem.hpp"
#include "GameContainer.hpp"
#include "SpawnMonsterSystem.hpp"

rtype::GameContainer::GameContainer() : _world{std::make_shared<ecs::World>()} {
	_initSystem();
}

void rtype::GameContainer::_initSystem() {
	_listSystem.emplace_back(new ecs::MovementSystem(_world->getAllEntities()));
	_listSystem.emplace_back(new ecs::RemoveSystem(_world->getAllEntities(), _world));
	_listSystem.emplace_back(new ecs::InputSystem(_world->getAllEntities(), _world));
//	_listSystem.emplace_back(new ecs::SpawnMonsterSystem(_world->getAllEntities(), _world, std::chrono::steady_clock::now()));
}

void rtype::GameContainer::runSystem() {
	for (auto &it : _listSystem)
		it->update(1);
}



