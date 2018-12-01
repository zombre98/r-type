//
// Created by Thomas Burgaud on 30/11/2018.
//

#pragma once

#include "System.hpp"
#include "World.hpp"

namespace ecs {
	class InGameBoardSystem : public System {
	public:
		explicit InGameBoardSystem(entityVector, std::shared_ptr<ecs::World>);

		void update(double delta) override;

	private:
		std::shared_ptr<ecs::World> _world;
	};
};
