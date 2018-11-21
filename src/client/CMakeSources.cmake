set(CORE
        main.cpp
        )

set(CLIENT
        App.cpp
        scenes/Scene.cpp
        events/SfmlEvents.hpp
        events/EventManager.cpp
        ResourceManager.hpp
        ../network/protocol.hpp
        ../server/engine/Components.hpp
        Client.hpp
        Client.cpp
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
