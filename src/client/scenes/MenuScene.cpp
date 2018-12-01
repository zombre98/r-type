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
	_evtMgr.subscribe<ConnectSuccess>(*this);
	_evtMgr.subscribe<ConnectTimeOut>(*this);
	_resourceMgr.loadAllTexturesInDirectory("");
	const auto &font = _resourceMgr.loadFont(fs::current_path() / "assets" / "font" / "prototype.ttf");
	_texts = {{"server", {sf::Text{"Server :", font, 50}, {600, 410}}},
		{"connect", {sf::Text{"Connect", font, 50}, {860, 600}}},
		{"address", {sf::Text{_address, font, 50}, {790, 410}}},
		{"failed_notice", {sf::Text{"", font, 40}, {710, 500}}}};
	_sprites = {{"background", sf::Sprite{_resourceMgr.getTexture("background")}},
		{"button_normal", sf::Sprite{_resourceMgr.getTexture("button_normal")}},
		{"button_hovered", sf::Sprite{_resourceMgr.getTexture("button_hovered")}}};
	_sprites["button_normal"].setPosition(800, 570);
	_sprites["button_hovered"].setPosition(800, 570);
	_texts["failed_notice"].t.setFillColor(sf::Color::Red);
	std::for_each(_texts.begin(), _texts.end(), [](auto &p) {
		p.second.t.setPosition(p.second.pos);
	});
}

void MenuScene::exit() noexcept {
	_evtMgr.unsubscribeAll(*this);
}

void MenuScene::update(float timeSinceLastFrame[[maybe_unused]]) noexcept {
	auto &window = _parent.getWindow();
	window.draw(_sprites["background"]);
	window.draw(_sprites["button_normal"]);
	if (const auto &mousePos = sf::Mouse::getPosition(); mousePos.x > 820 && mousePos.x < 1070 &&
		mousePos.y > 570 && mousePos.y < 700)
		window.draw(_sprites["button_hovered"]);
	std::for_each(_texts.begin(), _texts.end(), [&window](const auto &p) {
		window.draw(p.second.t);
	});
	if (_sprites.find("loading") != _sprites.end()) {
		_sprites["loading"].rotate(5);
		window.draw(_sprites["loading"]);
	}
}

void MenuScene::receive(const ConnectTimeOut &) noexcept {
	_sprites.erase("loading");
	_texts["failed_notice"].t.setString("Failed to connect to server");
}

void MenuScene::receive(const ConnectSuccess &) noexcept {
	_sprites.erase("loading");
	_parent.pushScene(create<GameScene>(_parent));
}

void MenuScene::receive(const SfmlEvent &event) noexcept {
	switch (event._event.type) {
	case sf::Event::KeyPressed:
		_texts["failed_notice"].t.setString("");
		if (event._event.key.code == sf::Keyboard::Escape) {
			_parent.getWindow().close();
		} else if (event._event.key.code == sf::Keyboard::Enter) {
			_tryConnection();
		}
		break;
	case sf::Event::TextEntered:
		_texts["failed_notice"].t.setString("");
		handleInput(event._event);
		break;
	case sf::Event::MouseButtonPressed: {
		_texts["failed_notice"].t.setString("");
		if (const auto &mousePos = sf::Mouse::getPosition(); mousePos.x > 820 && mousePos.x < 1070 &&
			mousePos.y > 570 && mousePos.y < 700)
			_tryConnection();
	}
	default:
		break;
	}
}

void MenuScene::handleInput(sf::Event textEvent) {
	std::cout << textEvent.text.unicode << std::endl;
	if ((textEvent.text.unicode >= '0' && textEvent.text.unicode <= '9') || textEvent.text.unicode == '.' ||
		textEvent.text.unicode == ':')
		_address += textEvent.text.unicode;
	else if (textEvent.text.unicode == 8)
		_address = _address.substr(0, _address.size() - 1);
	_texts["address"].t.setString(_address);
}

void MenuScene::_tryConnection() {
	_sprites.emplace("loading", sf::Sprite{_resourceMgr.getTexture("loading")});
	_sprites["loading"].setPosition(900, 500);
	_sprites["loading"].setOrigin(50, 50);
	auto ip = _address.substr(0, _address.find_first_of(':'));
	auto port = _address.substr(_address.find_first_of(':') + 1);
	std::cout << "trying " << ip << ":" << port << std::endl;
	_parent.getClient().connect(ip, port);
}
