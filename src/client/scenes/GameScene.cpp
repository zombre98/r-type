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
	_evtMgr.subscribe<net::EnemyType>(*this);
	_evtMgr.subscribe<net::ShotType>(*this);
	_resourceMgr.loadTexture("background.png");
        _bg.setTexture(_resourceMgr.getTexture("background"));
        _bg.scale(static_cast<float>(_parent.getWindow().getSize().x) /
                  _bg.getTexture()->getSize().x,
                  static_cast<float>(_parent.getWindow().getSize().y) /
                  _bg.getTexture()->getSize().y);
	_resourceMgr.loadAllTexturesInDirectory("");
}

void GameScene::update(float timeSinceLastFrame) noexcept {
	displayGame(timeSinceLastFrame);
}

void GameScene::displayGame(float timeSinceLastFrame[[maybe_unused]]) noexcept {
	auto &window = _parent.getWindow();
        _displayBg(window);
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
	auto it = _sprites.find(pos.head.id);
	std::cout << "[" << pos.head.id << "] Pos" << std::endl;
	if (it == _sprites.end())
		return;
	_sprites.at(pos.head.id).setPosition(pos.x, pos.y);
}

void GameScene::receive(const net::EnemyType &eType) {
	auto it = _sprites.find(eType.head.id);
	if (it != _sprites.end())
		return;
	if (eType.type == net::EnemyType::Enemy::CLASSIC) {
		std::cout << "Classic Enemy" << std::endl;
		_sprites.emplace(eType.head.id, _resourceMgr.getTexture("enemy1/frame00"));
		_sprites[eType.head.id].setPosition(-300, -300);
	}
}

void GameScene::receive(const net::ShotType &sType) {
	_sprites.emplace(sType.head.id, _resourceMgr.getTexture("shoot" + std::to_string(
			static_cast<int>(sType.type)) + "/frame0"));
}

void GameScene::_displayBg(sf::RenderWindow &window) {
    static std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    auto t2 = std::chrono::steady_clock::now();
    auto timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    window.draw(_bg);
    auto bgExtension = sf::Sprite{*(_bg.getTexture())};
    bgExtension.setScale(_bg.getScale());
    bgExtension.setPosition(_bg.getPosition().x + _bg.getTexture()->getSize().x * _bg.getScale().x,
                            _bg.getPosition().y);
    window.draw(bgExtension);

    if (timeSpan.count() < 1.f / BG_FPS)
        return;

    t1 = std::chrono::steady_clock::now();

    _bg.setPosition(_bg.getPosition().x - 2, _bg.getPosition().y);
    if (_bg.getPosition().x + _bg.getTexture()->getSize().x * _bg.getScale().x <= 0)
        _bg.setPosition(0, _bg.getPosition().y);
}
