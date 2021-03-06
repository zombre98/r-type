/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** GameContainer
*/

#pragma once

#include <list>
#include "World.hpp"
#include "System.hpp"
#include "Watcher.hpp"

namespace rtype {
	using systemPtr = std::unique_ptr<ecs::System>;
	class GameContainer {
	public:
		GameContainer();
		GameContainer(GameContainer &) = delete;
		GameContainer &operator=(GameContainer &) = delete;

		void runSystem();
		void resetSystem();
		std::shared_ptr<ecs::World> getWorld() const { return _world; }

		void checkWatcher();

	private:
		void _initSystem();


	private:
		std::list<systemPtr> _listSystem;
		std::shared_ptr<ecs::World> _world;
		lib::Watcher _watcher;
	};
}
