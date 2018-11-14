/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** GameScene
*/

#pragma once

#include <functional>
#include <unordered_map>
#include "events/SfmlEvents.hpp"
#include "Scene.hpp"

class GameScene final : public AScene, public Receiver {
	public:
	explicit GameScene(SceneManager &parent) noexcept : AScene(parent) {
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
