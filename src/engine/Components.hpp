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

	enum comp : std::size_t {
		COMP_ORIENTATION,
		COMP_VELOCITY,
		COMP_POSITION,
		MAX_COMPONENTS
	};

	struct Component {

	};

	struct Velocity : public Component {
		Velocity(float w, float v) : x(w), y(v)
		{};
		~Velocity() = default;
		static comp const type = COMP_VELOCITY;
		float x;
		float y;
	};

	struct Orientation : public Component{
		explicit Orientation(float ori) : orientation(ori)
		{};
		~Orientation() = default;
		static comp const type = COMP_ORIENTATION;
		float orientation;
	};

	struct Position : public Component {
		Position(float d, float v) : x(d), y(v)
		{};
		~Position() = default;
		static comp const type = COMP_POSITION;
		float x;
		float y;
	};
}
