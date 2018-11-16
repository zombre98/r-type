/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** App
*/

#pragma once

#include "scenes/Scene.hpp"

class App : public sf::RenderWindow {
	public:
	explicit App() : sf::RenderWindow(sf::VideoMode(1920, 1080), "R-Type",
		sf::Style::Close | sf::Style::Fullscreen), _sceneMgr(*this) {
	}

	void init();
	void run();
	private:
	SceneManager _sceneMgr;
};
