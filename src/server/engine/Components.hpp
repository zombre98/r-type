/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** rtype
*/

#pragma once

#include <memory>
#include <chrono>

namespace ecs {

	struct Component {
	};

	struct Player : public Component {
		explicit Player(std::size_t _id) : id{_id} {};
		~Player() = default;
		std::size_t id;
	};

	struct Velocity : public Component {
		Velocity(float w, float v) : x(w), y(v) {
		};
		~Velocity() = default;
		float x;
		float y;
	};

	struct Orientation : public Component {
		explicit Orientation(float ori) : orientation(ori) {
		};
		~Orientation() = default;
		float orientation;
	};

	struct Position : public Component {
		Position(int d, int v) : x(d), y(v) {
		};
		~Position() = default;
		int x;
		int y;
	};
}
