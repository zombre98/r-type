set(CORE
        main.cpp
        ../common/vec.hpp
        )

set(ENGINE
        engine/systems/Systems.hpp
        engine/systems/MovementSystem.cpp
        engine/Components.hpp
        engine/Entity.cpp
        engine/GameContainer.cpp
        )

set(SOURCES
        ${CORE}
        ${ENGINE}
        )
