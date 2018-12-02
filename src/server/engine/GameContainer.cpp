/*
** EPITECH PROJECT, 2017
** cpp_indie_studio
** File description:
** Created by armandmgt,
*/

#include <iostream>
#include "InputSystem.hpp"
#include "EnemiesMovementSystem.hpp"
#include "MovementSystem.hpp"
#include "CollisionSystem.hpp"
#include "InGameBoardSystem.hpp"
#include "RemoveSystem.hpp"
#include "GameContainer.hpp"
#include "EnemiesShootSystem.hpp"
#include "SpawnMonsterSystem.hpp"
#include "LuaSystem.hpp"

rtype::GameContainer::GameContainer() : _world{std::make_shared<ecs::World>()}, _watcher{"assets/libraries/"} {
    _initSystem();
    _watcher.run();
}

void rtype::GameContainer::_initSystem() {
	_listSystem.emplace_back(new ecs::InputSystem(_world->getAllEntities(), _world));
	_listSystem.emplace_back(new ecs::MovementSystem(_world->getAllEntities()));
	_listSystem.emplace_back(new ecs::RemoveSystem(_world->getAllEntities(), _world));
	_listSystem.emplace_back(new ecs::SpawnMonsterSystem(_world->getAllEntities(), _world, std::chrono::steady_clock::now()));
	_listSystem.emplace_back(new ecs::EnemiesMovementSystem(_world->getAllEntities(), std::chrono::steady_clock::now()));
        _listSystem.emplace_back(new ecs::LuaSystem<ecs::EnemyType, ecs::Velocity>(_world->getAllEntities(), "sinus_movement_system.lua"));
        _listSystem.emplace_back(new ecs::LuaSystem<ecs::ShotType, ecs::Velocity>(_world->getAllEntities(), "movement_shoot_system.lua"));
	_listSystem.emplace_back(new ecs::InGameBoardSystem(_world->getAllEntities(), _world));
	_listSystem.emplace_back(new ecs::CollisionSystem(_world->getAllEntities(), _world));
	_listSystem.emplace_back(new ecs::EnemiesShootSystem(_world->getAllEntities(), _world, std::chrono::steady_clock::now()));
}

void rtype::GameContainer::runSystem() {
	static auto last = std::chrono::steady_clock::now();

	auto delta = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::steady_clock::now() - last).count();
	last = std::chrono::steady_clock::now();
	for (auto &it : _listSystem)
            it->update(delta);
}

void rtype::GameContainer::checkWatcher() {
    static unsigned int index = 0;
    static std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    auto t2 = std::chrono::steady_clock::now();
    auto timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    if (timeSpan.count() < 10.f)
        return;

    if (index >= _watcher.getLoaders().size())
        return;
    auto entity = _watcher.getLoaders()[index]->getFunction<ecs::Entity *(*)()>("createEntity")();
    entity->id = entity->nextId++;
    _world->addEntity(entity);
    index++;
}

void rtype::GameContainer::resetSystem() {
		_listSystem.clear();
		_initSystem();
}
