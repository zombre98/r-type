//
// Created by Thomas Burgaud on 21/11/2018.
//

#pragma once

#include <memory>
#include <optional>
#include "System.hpp"
#include "Entity.hpp"

namespace ecs {
    using entityVector = std::shared_ptr<std::vector<entityPtr>>;

    class World {
    public:
        World() = default;
        ~World() = default;

        Entity &createEntity();
        void eraseEntity(std::size_t const &id);
	    ecs::Entity &createPlayer();
        void createClassicEnemies();
        void createShipEnemy();
        void createShot(const Position &pos, ShotType::Shot sType);
        entityVector getAllEntities() const noexcept { return entities; }

	    std::optional<Entity *> getEntity(entityId id) const {
		    auto it = std::find_if(entities->cbegin(), entities->cend(), [id](const entityPtr &e) {
			    return e->id == id;
		    });
		    if (it != entities->cend())
			    return it->get();
		    return std::nullopt;
	    }

        template<typename... Types>
        std::vector<Entity *> getEntities() {
            std::vector<Entity *> _entities;
            for (const auto &e : *entities) {
                if (passFilter<Types...>(e, TypeList<Types...>()))
                    _entities.push_back(e.get());
            }
            return _entities;
        }
    private:
        template<class... Types>
        bool passFilter(const std::unique_ptr<Entity> &entity[[maybe_unused]],
                        TypeList<Types...> tl[[maybe_unused]]) {
            return true;
        }

        template<class T, class... Types>
        bool passFilter(const std::unique_ptr<Entity> &entity, TypeList<T, Types...> tl[[maybe_unused]]) {
            return entity->hasComponent<T>() && passFilter<Types...>(entity, TypeList<Types...>());
        }

    private:
        entityVector entities{std::make_shared<std::vector<std::unique_ptr<Entity>>>()};
    };
}
