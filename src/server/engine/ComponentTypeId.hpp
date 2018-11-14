//
// Created by armandmgt on 11/13/18.
//

#pragma once

#include <cstddef>
#include <atomic>

using TypeId = std::size_t;

template<typename TBase>
class ComponentTypeId {
	template<typename T>
	static TypeId getTypeId() {
		static const TypeId id = _nextId++;
		return id;
	}

	private:
	static std::atomic<TypeId> _nextId;
};

template<typename TBase> std::atomic<TypeId> ComponentTypeId<TBase>::_nextId{0};
