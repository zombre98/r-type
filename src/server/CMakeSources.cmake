set(CORE
  main.cpp
  )

set(ENGINE
  engine/systems/InputSystem.cpp
  engine/Entity.hpp
  engine/Entity.cpp
  engine/ComponentId.hpp
  engine/ComponentId.cpp
  engine/systems/System.hpp
  engine/systems/LuaSystem.hpp
  engine/systems/MovementSystem.hpp
  engine/systems/MovementSystem.cpp
  engine/systems/CollisionSystem.hpp
  engine/systems/CollisionSystem.cpp
  engine/systems/SpawnMonsterSystem.hpp
  engine/systems/SpawnMonsterSystem.cpp
  engine/systems/MovementShootSystem.cpp
  engine/systems/MovementShootSystem.hpp
  engine/systems/InGameBoardSystem.cpp
  engine/systems/InGameBoardSystem.hpp
  engine/systems/EnemiesShootSystem.hpp
  engine/systems/EnemiesShootSystem.cpp
  engine/systems/EnemiesMovementSystem.hpp
  engine/systems/EnemiesMovementSystem.cpp
  engine/systems/RemoveSystem.hpp
  engine/systems/RemoveSystem.cpp
  engine/Components.hpp
  engine/GameContainer.hpp
  engine/GameContainer.cpp
  engine/World.cpp
  engine/World.hpp
  )

set(SERVER
  Server.hpp
  Server.cpp
  ProtocolServer.cpp
  ProtocolServer.hpp
  address.hpp
  address.cpp
  ../network/protocol.hpp
  address.hpp
  )

set(LIBRARY
  library/Watcher.cpp
  library/Loader.cpp
  )

set(SOURCES
  ${CORE}
  ${ENGINE}
  ${LIBRARY}
  ${SERVER}
  )
