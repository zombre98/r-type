include_directories(../lib/sol2)

set(SOURCE_FILES
        main.cpp
        engine/systems/Systems.hpp
        engine/systems/MovementSystem.hpp
        engine/systems/MovementSystem.cpp
        engine/Components.hpp
        engine/Entity.hpp
        engine/Entity.cpp
        engine/GameContainer.hpp
        engine/GameContainer.cpp
        common/vec.hpp
        )

if (WIN32)
    set(CMAKE_CXX_FLAGS "/W4 /permissive")
else ()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wfatal-errors")
endif ()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/engine/systems)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/engine)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/common)

if (WIN32)
    # TODO Add library linking under windows
else ()
    target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
    target_link_libraries(${PROJECT_NAME} lua)
endif ()
