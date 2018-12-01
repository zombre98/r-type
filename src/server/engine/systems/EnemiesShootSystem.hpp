//
// Created by Thomas Burgaud on 30/11/2018.
//

#pragma once

#include <World.hpp>
#include "System.hpp"

namespace ecs {
	class EnemiesShootSystem : public System {
	public:
		explicit EnemiesShootSystem(entityVector, std::shared_ptr<World> ,std::chrono::time_point<std::chrono::steady_clock>);

		void update(double delta) override;
	private:
		std::shared_ptr<ecs::World> _world;
		std::chrono::time_point<std::chrono::steady_clock> _lastClassicShoot;
		std::chrono::time_point<std::chrono::steady_clock> _lastShipShoot;
	};
};
