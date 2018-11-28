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
	explicit GameScene(SceneManager &parent) noexcept : AScene(parent,
		fs::current_path() / "assets" / "images" / "game") {
		_parent.getClient().connect("127.0.0.1", "8080");
		std::cout << static_cast<int>(net::protocolRType::CONNECTION) << std::endl;
		net::NetPlayer p{0, net::protocolRType::CONNECTION};
		_parent.getClient().sendData(p);
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
	private:
	void displayGame(float timeSinceLastFrame) noexcept;

	std::unordered_map<std::size_t, sf::Sprite> _sprites{};
	bool _started{false};
	bool _running{true};
};
