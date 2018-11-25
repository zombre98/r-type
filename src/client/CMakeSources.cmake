set(CORE
        main.cpp
        )

set(CLIENT
        App.cpp
        scenes/Scene.cpp
        events/SfmlEvent.hpp
        events/EventManager.hpp
        ResourceManager.hpp
        ../network/protocol.hpp
        ../server/engine/Components.hpp
        network/Client.hpp
        network/Client.cpp
        )

set(CLIENT_SCENES
        scenes/GameScene.cpp
        scenes/SplashScene.cpp
        scenes/MenuScene.cpp
        )

set(SOURCES
        ${CORE}
        ${CLIENT}
        ${CLIENT_SCENES}
        )
