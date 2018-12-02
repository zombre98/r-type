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
	_evtMgr.subscribe<net::Dead>(*this);
	_evtMgr.subscribe<net::Life>(*this);
	_evtMgr.subscribe<net::Score>(*this);
	_evtMgr.subscribe<net::Bonus>(*this);
	_resourceMgr.loadAllTexturesInDirectory("");
	const auto &font = _resourceMgr.loadFont(fs::current_path() / "assets" / "font" / "prototype.ttf");

	_score = {sf::Text{"Score : 0", font, 30}, {850, 1030}};
	_score.t.setPosition(_score.pos);
	_bg.setTexture(_resourceMgr.getTexture("background"));
	_bg.scale(static_cast<float>(_parent.getWindow().getSize().x) / _bg.getTexture()->getSize().x,
		static_cast<float>(_parent.getWindow().getSize().y) / _bg.getTexture()->getSize().y);
}

void GameScene::exit() noexcept {
}

void GameScene::update(float timeSinceLastFrame) noexcept {
	for (auto it = _animated.begin(), last = _animated.end(); it != last;) {
		const auto &nextFrame = it->second.addTime(timeSinceLastFrame);
		if (nextFrame) {
			_sprites[it->first].setTexture(_resourceMgr.getTexture(nextFrame.value()));
			it++;
		} else {
			_sprites.erase(it->first);
			it = _animated.erase(it);
		}
	}
	displayGame(timeSinceLastFrame);
}

void GameScene::displayGame(float timeSinceLastFrame[[maybe_unused]]) noexcept {
	auto &window = _parent.getWindow();
	_displayBg(window);
	window.draw(_score.t);
	for (auto &it : _sprites) {
		window.draw(it.second);
		auto recIt = _rectangles.find(it.first);
		if (recIt != _rectangles.end()) {
			window.draw(_rectangles.at(it.first));
		}
	}
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
	const auto &ship = _animated.emplace(player.head.id, _resourceMgr.copyOrLoadAnimation("ship" + std::to_string(player.id)));
	ship.first->second.setLoop(true);
	_sprites.emplace(player.head.id, _resourceMgr.getTexture(ship.first->second.getCurrent()));
}

void GameScene::receive(const net::Pos &pos) {
	auto it = _sprites.find(pos.head.id);
	if (it == _sprites.end()) {
		_parent.getClient().sendData(net::UnknownId{0, pos.head.id});
		return;
	}
	auto recIt = _rectangles.find(pos.head.id);
	if (recIt != _rectangles.end()) {
		_rectangles.at(pos.head.id).setPosition(pos.x -
				(_sprites.at(pos.head.id).getTexture()->getSize().x * _sprites.at(pos.head.id).getScale().x),
			pos.y - 5);
	}
	_sprites.at(pos.head.id).setPosition(pos.x, pos.y);
}

void GameScene::receive(const net::EnemyType &eType) {
	if (_sprites.find(eType.head.id) != _sprites.end())
		return;
	_sprites.emplace(eType.head.id,
		_resourceMgr.getTexture("enemy" + std::to_string(static_cast<int>(eType.type)) + "/frame00"));
	_sprites[eType.head.id].setPosition(-300, -300);
}

void GameScene::receive(const net::ShotType &sType) {
	_sprites.emplace(sType.head.id,
		_resourceMgr.getTexture("shoot" + std::to_string(static_cast<int>(sType.type)) + "/frame0"));
}

void GameScene::receive(const net::Dead &dead) {
	auto s = _sprites.find(dead.head.id);
	if (s == _sprites.end()) {
		_parent.getClient().sendData(net::UnknownId{0, dead.head.id});
		return;
	}
	_sprites.erase(s);
	auto r = _rectangles.find(dead.head.id);
	if (r != _rectangles.end())
		_rectangles.erase(r);
	auto explosionType = dead.isMonster ? "big-explosion" : "explosion";
	const auto &explosion = _animated.emplace(dead.head.id, _resourceMgr.copyOrLoadAnimation(explosionType));
	auto result = _sprites.emplace(dead.head.id, _resourceMgr.getTexture(explosion.first->second.getCurrent()));
	result.first->second.setPosition(dead.x, dead.y);
}

void GameScene::receive(const net::Life &life) {
	auto it = _rectangles.find(life.head.id);
	if (_sprites.find(life.head.id) == _sprites.end()) {
		return;
	}
	if (it != _rectangles.end()) {
		_rectangles.at(life.head.id).setSize(sf::Vector2f(static_cast<float>(life.lifePoint), 3));
		return;
	}
	_rectangles.emplace(life.head.id, sf::Vector2f(static_cast<float>(life.lifePoint), 3));
	_rectangles.at(life.head.id).setFillColor(sf::Color(100, 250, 50));
	_rectangles.at(life.head.id).setPosition(_sprites.at(life.head.id).getPosition().x -
			(_sprites.at(life.head.id).getTexture()->getSize().x * _sprites.at(life.head.id).getScale().x),
		_sprites.at(life.head.id).getPosition().y - 5);
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

void GameScene::receive(const net::Score &score) {
	_score.t.setString("Score : " + std::to_string(score.score));
}

void GameScene::receive(const net::Bonus &bonus) {
	if (_sprites.find(bonus.head.id) != _sprites.end())
		return;
	_sprites.emplace(bonus.head.id,
	                 _resourceMgr.getTexture("bonus" + std::to_string(static_cast<int>(bonus.type)) + "/frame00"));
	_sprites[bonus.head.id].setPosition(-300, -300);
}
