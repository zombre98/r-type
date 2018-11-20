set(CORE
        main.cpp
        ../common/vec.hpp
        )

set(ENGINE
        engine/Entity.hpp
        engine/ComponentId.hpp
        engine/systems/System.hpp
		engine/systems/LuaSystem.hpp
        engine/systems/MovementSystem.cpp
        engine/Components.hpp
        engine/GameContainer.cpp
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
