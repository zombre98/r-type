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
        Server.hpp
        Server.cpp
        ProtocolServer.cpp
        ProtocolServer.hpp
        ../network/protocol.hpp
        address.hpp
        )

set(SOURCES
        ${CORE}
        ${ENGINE}
        ${SERVER}
        )
