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
        engine/ComponentTypeId.hpp
        )

set(SERVER
        server.hpp
        server.cpp
        protocolServer.cpp
        protocolServer.hpp
        ../network/protocol.hpp
        )

set(SOURCES
        ${CORE}
        ${ENGINE}
        ${SERVER}
        )
