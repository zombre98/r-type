//
// Created by Thomas Burgaud on 23/11/2018.
//

#pragma once

#include "System.hpp"

namespace ecs {
	class RemoveSystem : public System {
	public:
		explicit RemoveSystem(entityVector);

		void update(double delta) override;
	};
};
