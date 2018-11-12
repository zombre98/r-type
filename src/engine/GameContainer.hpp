/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** GameContainer
*/

#pragma once

#include <stack>
#include <irrlicht/irrlicht.h>
#include "gfx/Renderer.hpp"
#include "world/World.hpp"
#include "event/Event.hpp"
#include "scenes/ScenesManager.hpp"
#include "music/Music.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

namespace ids {
	class GameContainer {
	public:
		explicit GameContainer(std::array<irr::EKEY_CODE, 5> &keymap);
		GameContainer(GameContainer &) = delete;
		GameContainer &operator=(GameContainer &) = delete;

		void start();

	private:
		std::shared_ptr<gfx::Renderer> _renderer;
		std::shared_ptr<Music> _music;
		ScenesManager _scenesManager;
		std::shared_ptr<ecs::World> _ecs;
	};
}
