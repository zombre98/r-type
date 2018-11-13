/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** SfmlEvent
*/

#pragma once

#include <SFML/Window/Event.hpp>
#include "EventManager.hpp"

class SfmlEvent : public BaseEvent {
	public:
	explicit SfmlEvent(sf::Event &event) noexcept : _event{event} {
	}

	public:
	sf::Event _event;
};
