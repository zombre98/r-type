if (WIN32)
    set(CMAKE_CXX_FLAGS "/W4 /permissive /EHsc")
else ()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wfatal-errors")
endif ()

add_subdirectory(client)
add_subdirectory(server)
