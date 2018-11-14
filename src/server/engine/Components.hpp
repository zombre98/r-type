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
		Position(float d, float v) : x(d), y(v) {
		};
		~Position() = default;
		float x;
		float y;
	};
}
