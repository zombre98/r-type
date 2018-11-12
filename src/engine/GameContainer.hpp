/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** GameContainer
*/

#pragma once

#include <stack>

#ifdef _IRR_WINDOWS_
#endif

namespace ids {
	class GameContainer {
	public:
		GameContainer() = default;
		GameContainer(GameContainer &) = delete;
		GameContainer &operator=(GameContainer &) = delete;

		void start();

	private:
	};
}
