/*
** EPITECH PROJECT, 2018
** GameScene
** File description:
** GameScene
*/

#include "GameScene.hpp"

void GameScene::enter() noexcept {
	_evtMgr.subscribe<SfmlEvent>(*this);
	_resourceMgr.loadTexture("background.png");
}

void GameScene::update(float timeSinceLastFrame) noexcept {
	displayGame(timeSinceLastFrame);
	_parent.getClient().pollOnce();
}

void GameScene::displayGame(float timeSinceLastFrame[[maybe_unused]]) noexcept {
	auto &window = _parent.getWindow();
	window.draw(sf::Sprite{_resourceMgr.getTexture("background")});
}

void GameScene::exit() noexcept {
}

void GameScene::receive(const SfmlEvent &event) noexcept {
	std::cout << "Receive : " << static_cast<int>(event._event.key.code) << std::endl;
	if (event._event.type == sf::Event::KeyPressed &&
		event._event.key.code == sf::Keyboard::Escape)
		_parent.getWindow().close();
}
