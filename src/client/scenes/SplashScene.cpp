/*
** EPITECH PROJECT, 2018
** SplashScene
** File description:
** SplashScene by armandmgt
*/

#include "GameScene.hpp"
#include "SplashScene.hpp"
#include "MenuScene.hpp"

void SplashScene::enter() noexcept {
	_evtMgr.subscribe<SfmlEvent>(*this);
	_resourceMgr.loadTexture("background.png");
	const auto &font = _resourceMgr.loadFont(
		fs::current_path() / "assets" / "font" / "prototype.ttf");
	_texts = {{sf::Text{"R-Type", font, 72}, {840, 450}}, {sf::Text{"Press SPACE to play", font}, {810, 650}}};
	std::for_each(_texts.begin(), _texts.end(), [](auto &tc) {
		tc.t.setPosition(tc.pos);
	});
}

void SplashScene::exit() noexcept {
	_evtMgr.unsubscribeAll(*this);
}

void SplashScene::update(float timeSinceLastFrame[[maybe_unused]]) noexcept {
	auto &window = _parent.getWindow();
	window.draw(sf::Sprite{_resourceMgr.getTexture("background")});
	std::for_each(_texts.begin(), _texts.end(), [&window](auto &tc) {
		window.draw(tc.t);
	});
}

void SplashScene::receive(const SfmlEvent &event) noexcept {
	if (event._event.type == sf::Event::KeyPressed) {
		if (event._event.key.code == sf::Keyboard::Escape) {
			_parent.getWindow().close();
		} else if (event._event.key.code == sf::Keyboard::Space) {
			_parent.changeScene(create<MenuScene>(_parent));
		}
	}
}
