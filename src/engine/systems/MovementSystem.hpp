/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MovementSystem
*/

#pragma once

#include "Systems.hpp"

namespace ecs {
	class MovementSystem : public System {
	public:
		MovementSystem(entityVector, std::shared_ptr<gfx::Renderer>);

		void update(double delta) override;
	private:
		bool _isValidPosition(float x, float y);
		std::shared_ptr<gfx::Renderer> _renderer;

		void _setAnimation(Entity *entity, bool walk);
	};
};