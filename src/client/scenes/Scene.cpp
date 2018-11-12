/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Scene by armandmgt
*/

#include "Scene.hpp"
#include "events/SfmlEvents.hpp"

void SceneManager::pushScene(std::unique_ptr<AScene> scenePtr) {
	if (!_scenes.empty())
		_scenes.top()->pause();
	_scenes.push(std::move(scenePtr));
	_scenes.top()->enter();
}

void SceneManager::popScene() {
	if (!_scenes.empty()) {
		_scenes.top()->exit();
		_scenes.pop();
		if (!_scenes.empty()) {
			_scenes.top()->resume();
		}
	}
}

void SceneManager::changeScene(std::unique_ptr<AScene> scenePtr) {
	popScene();
	pushScene(std::move(scenePtr));
}

void SceneManager::pauseScene() {
	if (!_scenes.empty())
		_scenes.top()->pause();
}

void SceneManager::resumeScene() {
	if (!_scenes.empty()) {
		_scenes.top()->resume();
	}
}

void SceneManager::popAllAndPushScene(std::unique_ptr<AScene> scenePtr) {
	while (!_scenes.empty()) {
		_scenes.pop();
	}
	pushScene(std::move(scenePtr));
}

void SceneManager::event(sf::Event &event) noexcept {
	/*
	 * Emit Keyboard events, Mouse events, Joystick events
	 */
	if (!_scenes.empty()) {
		_scenes.top()->_evtMgr.emit<SfmlEvent>(event);
	}
}

void SceneManager::update(float timeSinceLastFrame) noexcept {
	if (!_scenes.empty()) {
		_scenes.top()->update(timeSinceLastFrame);
	}
}
