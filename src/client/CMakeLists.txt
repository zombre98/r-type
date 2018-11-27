set(TARGET_NAME r-type_client)

include(CMakeSources.cmake)

add_executable(${TARGET_NAME} ${SOURCES})

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/..)
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/client)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/network)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/server/engine)

if (MSVC)
else ()
	target_link_libraries(${TARGET_NAME} PRIVATE stdc++fs)
endif ()

target_link_libraries(${TARGET_NAME} PRIVATE ${CONAN_LIBS})
