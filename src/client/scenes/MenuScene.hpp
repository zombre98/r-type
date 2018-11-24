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

namespace fs = std::filesystem;

class MenuScene final : public AScene, public Receiver {
	public:
	explicit MenuScene(SceneManager &parent) noexcept : AScene(parent,
		fs::current_path() / "assets" / "images" / "menu") {
		std::cout << "Create Menu Scene" << std::endl;
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
	std::vector<Texts> _texts;
};
