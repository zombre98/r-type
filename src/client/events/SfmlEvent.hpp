/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** SfmlEvent
*/

#pragma once

#include <SFML/Window/Event.hpp>
#include "EventManager.hpp"

struct SfmlEvent : BaseEvent {
	sf::Event _event;
};
