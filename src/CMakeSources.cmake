set(CORE
        main.cpp
        )

set(CLIENT
        client/App.cpp
        client/scenes/Scene.cpp
        client/events/SfmlEvents.hpp
        client/events/EventManager.hpp
        client/ResourceManager.hpp
        )

set(CLIENT_SCENES
        client/scenes/GameScene.cpp
        client/scenes/MenuScene.cpp
        )

set(SOURCES
        ${CORE}
        ${CLIENT}
        ${CLIENT_SCENES}
        )
