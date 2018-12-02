/*
** EPITECH PROJECT, 2018
** App
** File description:
** App by armandmgt
*/

#include "App.hpp"
#include "scenes/SplashScene.hpp"

void App::init() {
	_sceneMgr.pushScene<SplashScene>();
}

void App::runApp() {
	setFramerateLimit(60);
	sf::Clock deltaClock;

	while (isOpen()) {
		sf::Event sfEvent{};
		while (pollEvent(sfEvent))
			_sceneMgr.emit(sfEvent);
		_client.poll();
		clear();
		auto timeSinceLastFrame = deltaClock.getElapsedTime().asSeconds();
		_sceneMgr.update(timeSinceLastFrame);
		deltaClock.restart();
		display();
	}
}
