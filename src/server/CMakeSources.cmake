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
        engine/systems/SpawnMonsterSystem.hpp
        engine/systems/SpawnMonsterSystem.cpp
		engine/systems/RemoveSystem.hpp
		engine/systems/RemoveSystem.cpp
        engine/Components.hpp
        engine/GameContainer.cpp
		engine/World.cpp
		engine/World.hpp
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
