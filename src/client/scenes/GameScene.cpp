/*
** EPITECH PROJECT, 2018
** GameScene
** File description:
** GameScene
*/

#include "GameScene.hpp"

void GameScene::enter() noexcept {
	std::cout << "Start of GameScene" << std::endl;
	_evtMgr.subscribe<SfmlEvent>(*this);
	_resourceMgr.loadTexture("background.png");
	std::cout << "End of GameScene" << std::endl;
	_parent.getClient().connect("127.0.0.1", "8080");
	net::NetPlayer p{0, net::protocolRType::CONNECTION};
	_parent.getClient().sendData(p);
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
	if (event._event.type == sf::Event::KeyPressed &&
		event._event.key.code == sf::Keyboard::Escape)
		_parent.getWindow().close();
}
