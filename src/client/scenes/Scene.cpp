/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Scene by armandmgt
*/

#include "Scene.hpp"


void SceneManager::popScene() {
	if (!_scenes.empty()) {
		_scenes.top()->exit();
		_scenes.pop();
		if (!_scenes.empty()) {
			_scenes.top()->resume();
		}
	}
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

void SceneManager::update(float timeSinceLastFrame) noexcept {
	if (!_scenes.empty()) {
		_scenes.top()->update(timeSinceLastFrame);
	}
}
