/*
** EPITECH PROJECT, 2018
** GameScene
** File description:
** GameScene
*/

#include "GameScene.hpp"

void GameScene::enter() noexcept {
	_evtMgr.subscribe<SfmlEvent>(*this);
	_evtMgr.subscribe<net::NetPlayer>(*this);
	_evtMgr.subscribe<net::Pos>(*this);
	_resourceMgr.loadTexture("background.png");
	_resourceMgr.loadAllTexturesInDirectory("");
}

void GameScene::update(float timeSinceLastFrame) noexcept {
	displayGame(timeSinceLastFrame);
	_parent.getClient().pollOnce();
}

void GameScene::displayGame(float timeSinceLastFrame[[maybe_unused]]) noexcept {
	auto &window = _parent.getWindow();
	window.draw(sf::Sprite{_resourceMgr.getTexture("background")});
	for (auto &it : _sprites) {
		window.draw(it.second);
	}
}

void GameScene::exit() noexcept {
}

void GameScene::receive(const SfmlEvent &event) noexcept {
	if (event._event.type == sf::Event::KeyPressed) {
		switch (event._event.key.code) {
		case sf::Keyboard::Escape:
			_parent.getWindow().close();
			break;
		case sf::Keyboard::Left:
			_parent.getClient().sendData(net::Input{0, ecs::Input::Left});
			break;
		case sf::Keyboard::Right:
			_parent.getClient().sendData(net::Input{0, ecs::Input::Right});
			break;
		case sf::Keyboard::Up:
			_parent.getClient().sendData(net::Input{0, ecs::Input::Up});
			break;
		case sf::Keyboard::Down:
			_parent.getClient().sendData(net::Input{0, ecs::Input::Down});
			break;
		case sf::Keyboard::Space:
			_parent.getClient().sendData(net::Input{0, ecs::Input::Shoot});
			break;
		default:
			break;
		}
	}
}

void GameScene::receive(const net::NetPlayer &player) {
	_sprites.emplace(player.head.id, _resourceMgr.getTexture("ship" + std::to_string(player.id) + "/frame00"));
}

void GameScene::receive(const net::Pos &pos) {
	//	std::cout << pos.head.id << " Pos : " << pos.x << " " << pos.y << std::endl;
	_sprites.at(pos.head.id).setPosition(pos.x, pos.y);
}
