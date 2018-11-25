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
	explicit App() : sf::RenderWindow(sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Close | sf::Style::Fullscreen),
	                 _client{*this, _sceneMgr},
	                 _sceneMgr(*this, _client) {
	}

	void init();
	void runApp();
	private:
	net::Client _client;
	SceneManager _sceneMgr;
};
