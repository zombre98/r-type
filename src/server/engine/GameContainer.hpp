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

namespace rtype {
	class GameContainer {
	public:
		GameContainer();
		GameContainer(GameContainer &) = delete;
		GameContainer &operator=(GameContainer &) = delete;

		void runSystem();

	private:
		void _initSystem();

	private:
		std::list<std::unique_ptr<ecs::System>> _listSystem;
		std::shared_ptr<ecs::World> _world;
	};
}
