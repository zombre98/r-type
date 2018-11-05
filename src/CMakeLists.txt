set(SOURCE_FILES
        main.cpp
        )

if (WIN32)
    set(CMAKE_CXX_FLAGS "/W4 /permissive")
else ()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wfatal-errors")
endif ()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if (WIN32)
    # TODO Add library linking under windows
else ()
    target_link_libraries(${PROJECT_NAME} sfml-system sfml-graphics sfml-audio)
endif ()
