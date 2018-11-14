set(TARGET_NAME r-type_client)

include(CMakeSources.cmake)

add_executable(${TARGET_NAME} ${SOURCES})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE stdc++fs)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/client)

if (WIN32)
    # TODO Add library linking under windows
else ()
    target_link_libraries(${TARGET_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
endif ()
