/*
** EPITECH PROJECT, 2018
** SplashScene
** File description:
** SplashScene
*/

#pragma once

#include <experimental/filesystem>
#include "Scene.hpp"
#include "events/SfmlEvents.hpp"

namespace fs = std::experimental::filesystem;

class SplashScene final : public AScene, public Receiver {
	public:
	explicit SplashScene(SceneManager &parent) noexcept : AScene(parent,
		fs::current_path().parent_path() / "assets" / "images" / "menu") {
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
