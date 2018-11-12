set(CORE
        main.cpp
        common/vec.hpp
        )

set(ENGINE
        engine/systems/Systems.hpp
        engine/systems/MovementSystem.cpp
        engine/Components.hpp
        engine/Entity.cpp
        engine/GameContainer.cpp
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
        ${ENGINE}
        ${CLIENT}
        ${CLIENT_SCENES}
        )
