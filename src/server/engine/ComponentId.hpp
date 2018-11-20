//
// Created by armandmgt on 11/13/18.
//

#pragma once

#include <cstddef>
#include <atomic>

using TypeId = std::size_t;

class ComponentId {
	public:
	template<typename T>
	static TypeId getTypeId() {
		static const TypeId id = _nextId++;
		return id;
	}

	private:
	static std::atomic<TypeId> _nextId;
};

inline std::atomic<TypeId> ComponentId::_nextId{0};
