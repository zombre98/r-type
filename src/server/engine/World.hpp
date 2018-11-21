//
// Created by Thomas Burgaud on 21/11/2018.
//

#pragma once

#include <memory>
#include "Entity.hpp"

namespace ecs {
	using entityVector = std::shared_ptr<std::vector<std::unique_ptr<Entity>>>;

	class World {
	public:
		World() = default;
		~World() = default;

		Entity &createEntity();
		entityVector getEntities() const noexcept { return entities; }

	private:
		entityVector entities;

	};
}
