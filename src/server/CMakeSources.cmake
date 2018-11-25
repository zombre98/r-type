set(CORE
        main.cpp
        ../common/vec.hpp
        )

set(ENGINE
        engine/Entity.hpp
        engine/Entity.cpp
        engine/ComponentId.hpp
        engine/ComponentId.cpp
        engine/systems/System.hpp
         engine/systems/LuaSystem.hpp
        engine/systems/MovementSystem.hpp
        engine/systems/MovementSystem.cpp
        engine/Components.hpp
        engine/GameContainer.hpp
        engine/GameContainer.cpp
        )

set(SERVER
        Server.hpp
        Server.cpp
        ProtocolServer.cpp
        ProtocolServer.hpp
        ../network/protocol.hpp
        address.cpp
        )

set(SOURCES
        ${CORE}
        ${ENGINE}
        ${SERVER}
        )
