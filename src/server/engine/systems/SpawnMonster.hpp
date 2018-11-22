//
// Created by Thomas Burgaud on 22/11/2018.
//

#pragma once

#include <chrono>
#include "World.hpp"
#include "System.hpp"

namespace ecs {
	class SpawnMonster : public System {
	public:
		explicit SpawnMonster(entityVector, std::shared_ptr<ecs::World> world, std::chrono::time_point<std::chrono::steady_clock>);

		void update(double delta) override;

	private:
		std::shared_ptr<ecs::World> _world;
		std::chrono::time_point<std::chrono::steady_clock> lastSpawn;
	};
}
