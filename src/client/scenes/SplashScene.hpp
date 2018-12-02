/*
** EPITECH PROJECT, 2018
** SplashScene
** File description:
** SplashScene
*/

#pragma once

#include <experimental/filesystem>
#include "Scene.hpp"
#include "events/SfmlEvent.hpp"

namespace fs = std::filesystem;

class SplashScene final : public AScene, public Receiver {
	public:
	explicit SplashScene(SceneManager &parent) noexcept : AScene(parent,
		fs::current_path() / "assets" / "images" / "splash") {
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

	private:
	std::vector<Texts> _texts;
	bool _next{false};
};
