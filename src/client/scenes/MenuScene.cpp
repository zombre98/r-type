/*
** EPITECH PROJECT, 2018
** MenuScene
** File description:
** MenuScene by armandmgt
*/

#include "GameScene.hpp"
#include "MenuScene.hpp"

void MenuScene::enter() noexcept {
	_evtMgr.subscribe<SfmlEvent>(*this);
}

void MenuScene::exit() noexcept {
}

void MenuScene::update(float timeSinceLastFrame[[maybe_unused]]) noexcept {
}

void MenuScene::receive(const SfmlEvent &event) noexcept {
	if (event._event.type == sf::Event::KeyPressed) {
		if (event._event.key.code == sf::Keyboard::Escape) {
			_parent.getWindow().close();
		} else if (event._event.key.code == sf::Keyboard::Space) {
			AScene::create<GameScene>(_parent);
		}
	}
}
