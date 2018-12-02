//
// EPITECH PROJECT, 2018
// Scene
// File description:
// SceneManager
//

#pragma once

#include <stack>
#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "network/Client.hpp"
#include "events/EventManager.hpp"
#include "events/SfmlEvent.hpp"
#include "ResourceManager.hpp"
#include "protocol.hpp"

struct Texts {
	sf::Text t;
	sf::Vector2f pos;
};

class SceneManager;

class AScene {
	protected:
	explicit AScene(SceneManager &parent) :
		_parent(parent) {
	}

	AScene(SceneManager &parent, const fs::path &resourcePath) :
		_resourceMgr(resourcePath),
		_parent(parent) {
	}

	public:
	virtual ~AScene() = default;

	/*
	 * Scene Manipulation
	 */
	virtual void enter() = 0;
	virtual void exit() = 0;

	virtual void pause() {
	}

	virtual void resume() {
	}

	virtual void update(float timeSinceLastFrame) = 0;

	public:
	EventManager _evtMgr;
	protected:
	ResourceManager _resourceMgr;
	SceneManager &_parent;
};

namespace net {
	class Client;
}

class SceneManager {
	public:
	explicit SceneManager(sf::RenderWindow &window, net::Client &client) :
		_window(window),
		_client(client) {
	}

	/*
	 * Create a scene
	 */
	template<typename T>
	std::unique_ptr<T> create() noexcept {
		static_assert(std::is_base_of<AScene, T>(), "Template parameter is not based of AScene");
		return std::make_unique<T>(*this);
	}

	template<typename EventType>
	void emit(EventType event) noexcept {
		static_assert(std::is_base_of<BaseEvent, EventType>(), "BaseEvent is not a base of EventType");
		/*
		 * Emit received packages as events
		 */
		if (!_scenes.empty()) {
			_scenes.top()->_evtMgr.emit<EventType>(event);
		}
	}

	void update(float timeSinceLastFrame) noexcept;

	/*
	 * Scenes Handlers
	 */
	template<typename T>
	void pushScene() {
		if (!_scenes.empty())
			_scenes.top()->pause();
		_scenes.push(create<T>());
		_scenes.top()->enter();
	}

	template<typename T>
	void changeScene() {
		popScene();
		pushScene<T>();
	}

	void popScene();
	void pauseScene();
	void resumeScene();

	template<typename T>
	void popAllAndPushScene() {
		while (!_scenes.empty()) {
			_scenes.pop();
		}
		pushScene<T>();
	}

	/*
	 * Getters
	 */
	sf::RenderWindow &getWindow() const noexcept {
		return _window;
	}

	net::Client &getClient() const noexcept {
		return _client;
	}

	private:
	sf::RenderWindow &_window;
	net::Client &_client;
	std::stack<std::unique_ptr<AScene>> _scenes;
};

template<>
inline void SceneManager::emit(sf::Event event) noexcept {
	/*
	 * Emit Keyboard, Mouse and Joystick events wrapped in SfmlEvent
	 */
	emit(SfmlEvent{{}, event});
}
