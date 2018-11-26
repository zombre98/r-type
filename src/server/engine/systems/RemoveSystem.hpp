//
// Created by Thomas Burgaud on 23/11/2018.
//

#pragma once

#include "System.hpp"
#include "World.hpp"

namespace ecs {
	class RemoveSystem : public System {
	public:
		explicit RemoveSystem(entityVector entities, ecs::World &world);

		void update(double delta) override;

	private:
		ecs::World &_world;
	};
};
