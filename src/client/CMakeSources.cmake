set(CORE
        main.cpp
        ../common/vec.hpp
        )

set(CLIENT
        App.cpp
        ../server/engine/ComponentId.cpp
        ../server/engine/ComponentId.hpp
        scenes/Scene.cpp
        events/SfmlEvent.hpp
        events/EventManager.hpp
        events/EventManager.cpp
        ResourceManager.hpp
        ../network/protocol.hpp
        ../server/engine/Components.hpp
        network/Client.hpp
        network/Client.cpp
        )

set(CLIENT_SCENES
        scenes/GameScene.cpp
        scenes/GameScene.hpp
        scenes/SplashScene.cpp
        scenes/SplashScene.hpp
        scenes/MenuScene.cpp
        scenes/MenuScene.hpp
        )

set(SOURCES
        ${CORE}
        ${CLIENT}
        ${CLIENT_SCENES}
        )
