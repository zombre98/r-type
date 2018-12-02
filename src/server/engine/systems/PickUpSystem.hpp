//
// Created by Thomas Burgaud on 02/12/2018.
//

#pragma once

#include "World.hpp"
#include "System.hpp"

namespace ecs {
	class PickUpSystem : public System {
	public:
		PickUpSystem(entityVector,	std::shared_ptr<World>);

		void update(double delta) override;
	private:
		std::shared_ptr<ecs::World> _world;
	};
};
