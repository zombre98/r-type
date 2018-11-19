set(CORE
        main.cpp
        ../common/vec.hpp
        )

set(ENGINE
        engine/Entity.hpp
        engine/ComponentId.hpp
        engine/systems/System.hpp
        engine/systems/MovementSystem.cpp
        engine/Components.hpp
        engine/GameContainer.cpp
        )

set(SOURCES
        ${CORE}
        ${ENGINE}
        )
