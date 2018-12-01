/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** GameScene
*/

#pragma once

#include <functional>
#include <unordered_map>
#include "events/SfmlEvent.hpp"
#include "Scene.hpp"
#include "protocol.hpp"

class GameScene final : public AScene, public Receiver {
	public:
    static constexpr int BG_FPS = 120;

	explicit GameScene(SceneManager &parent) noexcept : AScene(parent,
		fs::current_path() / "assets" / "images" / "game") {
	}

	/*
	 * Scene Manipulation
	 */
	void enter() noexcept override;
	void exit() noexcept override;
	void update(float timeSinceLastFrame) noexcept override;

	public:
	/*
	 * Events Callback
	 */
	void receive(const SfmlEvent &event) noexcept;
	void receive(const net::NetPlayer &player);
	void receive(const net::Pos &pos);
	void receive(const net::EnemyType &eType);
	void receive(const net::ShotType &sType);
	void receive(const net::Dead &dead);
	void receive(const net::Life &life);
	private:
	void displayGame(float timeSinceLastFrame) noexcept;

	private:
	std::unordered_map<std::size_t, sf::Sprite> _sprites;
	std::unordered_map<std::size_t, sf::RectangleShape> _rectangles;
	bool _started{false};
	bool _running{true};
    sf::Sprite _bg;

	void _displayBg(sf::RenderWindow &);
};
