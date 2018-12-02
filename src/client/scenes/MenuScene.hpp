/*
** EPITECH PROJECT, 2018
** MenuScene
** File description:
** MenuScene
*/

#pragma once

#include <experimental/filesystem>
#include "Scene.hpp"
#include "events/SfmlEvent.hpp"
#include "events/ConnectState.hpp"

namespace fs = std::filesystem;

class MenuScene final : public AScene, public Receiver {
	public:
	explicit MenuScene(SceneManager &parent) noexcept : AScene(parent,
		fs::current_path() / "assets" / "images" / "menu") {
	}

	/*
	 * Scene Manipulation
	 */
	void enter() noexcept final;
	void exit() noexcept final;
	void update(float timeSinceLastFrame) noexcept override;
	public:
	/*
	 * Events Callback
	 */
	void receive(const SfmlEvent &event) noexcept;
	void receive(const ConnectTimeOut &event) noexcept;
	void receive(const ConnectSuccess &event) noexcept;

	private:
	std::map<std::string, sf::Sprite> _sprites;
	std::map<std::string, Texts> _texts;
	void handleInput(sf::Event key);
	std::string _address;
	void _tryConnection();
};
