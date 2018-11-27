if (WIN32)
    string(APPEND CMAKE_CXX_FLAGS "/W4 /permissive /EHsc /std:c++17")
else ()
    string(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -Wfatal-errors")
endif ()

include(CMakeSources.cmake)

add_subdirectory(client)
add_subdirectory(server)
