/*
** EPITECH PROJECT, 2018
** App
** File description:
** App by armandmgt
*/

#include "App.hpp"
#include "scenes/SplashScene.hpp"

void App::init() {
	_sceneMgr.pushScene(AScene::create<SplashScene>(_sceneMgr));
}

void App::runApp() {
	setFramerateLimit(60);
	sf::Clock deltaClock;

	while (isOpen()) {
		sf::Event sfEvent{};
		while (pollEvent(sfEvent) || poll()) {
			_sceneMgr.emit(sfEvent);
		}
		clear();
		auto timeSinceLastFrame = deltaClock.getElapsedTime().asSeconds();
		_sceneMgr.update(timeSinceLastFrame);
		display();
	}
}
