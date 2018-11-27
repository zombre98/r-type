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
	_resourceMgr.loadTexture("play_background.png");
	const auto &font = _resourceMgr.loadFont(
		fs::current_path() / "assets" / "font" / "prototype.ttf");
	_texts = {{sf::Text{"R-Type", font, 72}, {840, 450}}, {sf::Text{"Press SPACE to play", font}, {810, 650}}};
	std::for_each(_texts.begin(), _texts.end(), [](auto &tc) {
		tc.t.setPosition(tc.pos);
	});
}

void MenuScene::exit() noexcept {
}

void MenuScene::update(float timeSinceLastFrame[[maybe_unused]]) noexcept {
	auto &window = _parent.getWindow();
	window.draw(sf::Sprite{_resourceMgr.getTexture("play_background")});
	std::for_each(_texts.begin(), _texts.end(), [&window](auto &tc) {
		window.draw(tc.t);
	});
}

void MenuScene::receive(const SfmlEvent &event) noexcept {
	if (event._event.type == sf::Event::KeyPressed) {
		if (event._event.key.code == sf::Keyboard::Escape) {
			_parent.getWindow().close();
		} else if (event._event.key.code == sf::Keyboard::Space) {
			_parent.pushScene(create<GameScene>(_parent));
		}
	}
}
