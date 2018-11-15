set(SOURCE_FILES
        main.cpp
        server/server.hpp
        server/server.cpp
        server/protocolServer.cpp
        server/protocolServer.hpp
        network/protocol.hpp
        )

if (WIN32)
    set(CMAKE_CXX_FLAGS "/W4 /permissive")
else ()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wfatal-errors")
endif ()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/network)

if (WIN32)
    # TODO Add library linking under windows
else ()
    find_package(Boost 1.42.0 REQUIRED COMPONENTS system thread regex)
    IF(Boost_FOUND)
        INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
        LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    ENDIF(Boost_FOUND)
    SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})
    target_link_libraries(${PROJECT_NAME} ${USED_LIBS})
endif ()
