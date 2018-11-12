/*
** EPITECH PROJECT, 2018
** GameScene
** File description:
** GameScene
*/

#include "GameScene.hpp"

void GameScene::update(float timeSinceLastFrame) noexcept {
	displayGame(timeSinceLastFrame);
}

void GameScene::displayGame(float timeSinceLastFrame[[maybe_unused]]) noexcept {
}

void GameScene::enter() noexcept {
	_evtMgr.subscribe<SfmlEvent>(*this);
}

void GameScene::exit() noexcept {
}

void GameScene::receive(const SfmlEvent &event) noexcept {
	if (event._event.type == sf::Event::KeyPressed &&
		event._event.key.code == sf::Keyboard::Escape)
		_parent.getWindow().close();
}
