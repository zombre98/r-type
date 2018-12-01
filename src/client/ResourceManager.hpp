//
// EPITECH PROJECT, 2018
// r-type
// File description:
// ResourcesManager
//

#pragma once

#include <utility>
#include <iostream>
#include <unordered_map>
#include <filesystem>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

template<typename Resource>
class ResourceHolder {
	public:
	explicit ResourceHolder() = default;

	template<typename ...Args>
	Resource &load(const std::string &id, Args &&...args) {
		Resource res;

		if (!res.loadFromFile(std::forward<Args>(args)...)) {
			throw std::runtime_error("Impossible to load file");
		}

		if (!_resources.emplace(id, std::move(res)).second) {
			std::cout << "Object already exists" << std::endl;
			return get(id);
		}
		return _resources[id];
	}

	void remove(const std::string &id) noexcept {
		if (_resources.find(id) != _resources.end()) {
			_resources.erase(id);
		}
	}

	Resource &get(const std::string &id) {
		return _resources.at(id);
	}

	template<typename ...Args>
	Resource &getOrLoad(const std::string &id, Args &&...args) {
		if (_resources.find(id) == _resources.end()) {
			return load(id, std::forward<Args>(args)...);
		}
		return get(id);
	}

	void clear() noexcept {
		_resources.clear();
	}

	private:
	std::unordered_map<std::string, Resource> _resources;
};

class AnimationState {
	public:
	explicit AnimationState() = default;

	AnimationState(const AnimationState &oth) noexcept {
		_animations = oth._animations;
		_loop = oth._loop;
		_frameRate = oth._frameRate;
	}

	std::set<std::string> &getAnimations() noexcept {
		return _animations;
	}

	std::optional<std::string> addTime(float timeSinceLastFrame) noexcept {
		_time += timeSinceLastFrame;
		if (_time > _frameRate * _animations.size()) {
			if (!_loop)
				return std::nullopt;
			_time = 0;
			_index = 0;
		}
		if (_time > _frameRate * (_index + 1))
			_index += 1;
		return *std::next(_animations.begin(), _index);
	}

	void setFrameRate(float frameRate) noexcept {
		_frameRate = frameRate;
	}

	void setLoop(bool loop) noexcept {
		_loop = loop;
	}

	const std::string &getCurrent() const noexcept {
		return *std::next(_animations.begin(), _index);
	}

	private:
	bool _loop{false};
	float _frameRate{0.2f};
	float _time{0};
	size_t _index{0};
	std::set<std::string> _animations{};
};

class ResourceManager {
	public:
	using MusicRegistry = ResourceHolder<sf::Music>;
	using TexturesRegistry = ResourceHolder<sf::Texture>;
	using FontsRegistry = ResourceHolder<sf::Font>;

	explicit ResourceManager(
		fs::path resourceDirectoryPath = (fs::current_path() / "assets")) noexcept
		: _resourceDirectoryPath{std::move(resourceDirectoryPath)} {
	}

	public:
	/*
	 * Just give it the texture's name
	 * If the texture is in _resourceDirectoryPath(default = "assets/")
	 */
	sf::Texture &loadTexture(const fs::path &filename) {
		for (const auto &it : fs::recursive_directory_iterator(_resourceDirectoryPath)) {
			if (it.status().type() != fs::file_type::directory) {
				if (it.path().filename() == filename) {
					auto id = it.path().stem();
					if (it.path().parent_path() != _resourceDirectoryPath)
						id = it.path().parent_path().filename() / id;
					return _texturesRegistry.load(id, it.path());
				}
			}
		}
		return _texturesRegistry.load(std::move(filename.stem()), filename);
	}

	void loadAllTexturesInDirectory(const fs::path &filename) {
		for (const auto &sub : fs::recursive_directory_iterator(_resourceDirectoryPath / filename)) {
			if (sub.status().type() != fs::file_type::directory) {
				auto id = sub.path().stem();
				if (sub.path().parent_path() != _resourceDirectoryPath)
					id = sub.path().parent_path().filename() / id;
				_texturesRegistry.load(id, sub.path());
			}
		}
	}

	sf::Texture &getTexture(const std::string &id) noexcept {
		return _texturesRegistry.get(id);
	}

	void remove(const std::string &id) {
		_texturesRegistry.remove(id);
	}

	AnimationState &loadAnimation(const fs::path &filename) {
		/*
		 * Search for the animation directory
		 */
		for (const auto &sub : fs::directory_iterator(_resourceDirectoryPath / filename)) {
			loadTexture(sub.path());
			_animations[filename].getAnimations().insert(
				sub.path().parent_path().filename() / sub.path().stem());
		}
		return _animations[filename];
	}

	AnimationState &copyOrLoadAnimation(const std::string &id) noexcept {
		if (_animations.find(id) != _animations.end())
			return _animations[id];
		return loadAnimation(id);
	}

	sf::Font &loadFont(const fs::path &filename) {
		for (auto &it : fs::recursive_directory_iterator(_resourceDirectoryPath)) {
			if (it.status().type() != fs::file_type::directory) {
				if (it.path().filename() == filename) {
					return _fontsRegistry.load(std::move(filename.stem()), it.path());
				}
			}
		}
		return _fontsRegistry.load(std::move(filename.stem()), filename);
	}

	sf::Font getFont(const std::string &id) {
		return _fontsRegistry.get(id);
	}

	private:
	fs::path _resourceDirectoryPath;

	TexturesRegistry _texturesRegistry;
	FontsRegistry _fontsRegistry;
	std::unordered_map<std::string, AnimationState> _animations;
};
