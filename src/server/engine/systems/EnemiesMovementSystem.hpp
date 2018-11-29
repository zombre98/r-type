//
// Created by Thomas Burgaud on 29/11/2018.
//

#pragma once

#include "System.hpp"

namespace ecs {
	class EnemiesMovementSystem : public System {
	public:
		explicit EnemiesMovementSystem(entityVector, std::chrono::time_point<std::chrono::steady_clock>);

		void update(double delta) override;

	private:
		std::chrono::time_point<std::chrono::steady_clock> _lastMove;
	};
};
