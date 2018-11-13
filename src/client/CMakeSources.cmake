set(CORE
        main.cpp
        ../common/vec.hpp
        )

set(CLIENT
        App.cpp
        scenes/Scene.cpp
        events/SfmlEvents.hpp
        events/EventManager.hpp
        ResourceManager.hpp
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
