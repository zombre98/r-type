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

class GameScene final : public AScene, public Receiver {
	public:
	explicit GameScene(SceneManager &parent) noexcept : AScene(parent,
		fs::current_path() / "assets" / "images" / "game") {
		_parent.getClient().restart();
		_parent.getClient().connect("127.0.0.1", "8080");
		std::cout << "1 : "<< _parent.getClient()._ioContext.stopped() << std::endl;
		net::NetPlayer p{0, net::protocolRType::CONNECTION};
		_parent.getClient().asyncSendData(p);
		std::cout << "2 : "<< _parent.getClient()._ioContext.stopped() << std::endl;
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
	private:
	void displayGame(float timeSinceLastFrame) noexcept;

	bool _started{false};
	bool _running{true};
};
