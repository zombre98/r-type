/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Systems
*/

#pragma once

#include <utility>
#include <algorithm>
#include "Entity.hpp"

namespace ecs {
	using entityPtr = std::unique_ptr<Entity>;
	using entityVector = std::shared_ptr<std::vector<entityPtr>>;

	template<typename... Types>
	struct TypeList {
	};

	class System {
		public:
		explicit System(entityVector allEntities) : _allEntities(std::move(allEntities)) {
		};
		virtual void update(double delta) = 0;

		template<typename... Types>
		std::vector<Entity *> getEntities() {
			std::vector<Entity *> _entities;
			for (const auto &e : *_allEntities) {
				if (passFilter<Types...>(e, TypeList<Types...>()))
					_entities.push_back(e.get());
			}
			return _entities;
		}
		private:
		template<class... Types>
		bool passFilter(const std::unique_ptr<Entity> &entity[[maybe_unused]],
			TypeList<Types...> tl[[maybe_unused]]
		) {
			return true;
		}

		template<class T, class... Types>
		bool passFilter(const std::unique_ptr<Entity> &entity, TypeList<T, Types...> tl[[maybe_unused]]) {
			return entity->hasComponent<T>() && passFilter<Types...>(entity, TypeList<Types...>());
		}

		protected:
		entityVector _allEntities;
	};
};
