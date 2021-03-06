/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** MovementSystem
*/

#pragma once

#include "System.hpp"

namespace ecs {
	class MovementSystem : public System {
	public:
		explicit MovementSystem(entityVector);

		void update(double delta) override;
	private:
		bool _isValidPosition(float x, float y);
	};
};
