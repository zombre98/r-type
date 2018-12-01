/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** Entities
*/

#pragma once

#include <bitset>
#include <vector>
#include <array>
#include "Components.hpp"
#include "ComponentId.hpp"

constexpr std::size_t MAX_COMPONENTS = 256;

namespace ecs {

	using entityId = unsigned long;

	class Entity {
	public:
		Entity() : bit{0}, id{nextId++}, componentArray{nullptr} {};
		Entity(Entity &) = delete;
		Entity &operator=(Entity &) = delete;
		Entity(Entity &&) = default;
		Entity &operator=(Entity &&) = default;

		template<class T>
		T &getComponent() {
			static_assert(std::is_base_of<Component, T>(), "T is not a component");
			if (!bit[ComponentId::getTypeId<T>()])
				throw std::runtime_error("Entity has no T component");
			return static_cast<T &>(*componentArray[ComponentId::getTypeId<T>()]);
		}

		template<class T>
		const T &getComponent() const {
			static_assert(std::is_base_of<Component, T>(), "T is not a component");
			if (!bit[ComponentId::getTypeId<T>()])
				throw std::runtime_error("Entity has no T component");
			return static_cast<T &>(*componentArray[ComponentId::getTypeId<T>()]);
		}

		template<class T>
		bool hasComponent() const {
			static_assert(std::is_base_of<Component, T>(), "T is not a component");
			return bit[ComponentId::getTypeId<T>()];
		}

		template <typename T, typename... Args>
		void addComponent(Args&&... args) {
			static_assert(std::is_base_of<Component, T>(), "T is not a component");
			bit[ComponentId::getTypeId<T>()] = true;
			componentArray[ComponentId::getTypeId<T>()] = std::unique_ptr<T>(
				new T{std::forward<Args>(args)...});
		}

		template<class T>
		void removeComponent() {
			static_assert(std::is_base_of<Component, T>(), "T is not a component");
			bit[ComponentId::getTypeId<T>()] = false;
			componentArray[ComponentId::getTypeId<T>()].reset(nullptr);
		}

	public:
		std::bitset<MAX_COMPONENTS> bit;
		std::size_t id;
        public:
		static std::size_t nextId;
		std::array<std::unique_ptr<Component>, MAX_COMPONENTS> componentArray;
	};
}
