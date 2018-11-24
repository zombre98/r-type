/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** App
*/

#pragma once

#include "scenes/Scene.hpp"
#include "network/Client.hpp"

class App : public sf::RenderWindow, public ba::io_context {
	public:
	explicit App() : sf::RenderWindow(sf::VideoMode(1920, 1080), "R-Type", sf::Style::Close | sf::Style::Fullscreen),
		_sceneMgr(*this, _client),
		_client{*this, _sceneMgr} {
	}

	void init();
	void runApp();
	private:
	SceneManager _sceneMgr;
	net::Client _client;
};
