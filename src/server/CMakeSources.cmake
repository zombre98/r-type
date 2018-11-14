set(CORE
        main.cpp
        ../common/vec.hpp
        )

set(ENGINE
        engine/systems/System.hpp
		engine/systems/LuaSystem.cpp
        engine/systems/MovementSystem.cpp
        engine/Components.hpp
        engine/Entity.cpp
        engine/GameContainer.cpp
        )

set(SOURCES
        ${CORE}
        ${ENGINE}
        )
