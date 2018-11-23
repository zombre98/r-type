//
// Created by Thomas Burgaud on 23/11/2018.
//

#pragma once

#include "System.hpp"
#include "World.hpp"

namespace ecs {
	class RemoveSystem : public System {
	public:
		explicit RemoveSystem(entityVector entities, std::shared_ptr<ecs::World> world);

		void update(double delta) override;

	private:
		std::shared_ptr<ecs::World> _world;
	};
};
