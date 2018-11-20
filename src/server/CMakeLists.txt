include(CMakeSources.cmake)

set(TARGET_NAME r-type_server)

add_executable(${TARGET_NAME} ${SOURCES} ${COMMON})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/common)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/server/engine)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/server/engine/systems)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/network)

target_link_libraries(${TARGET_NAME} PRIVATE ${BOOST_LIBS})
