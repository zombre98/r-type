set(TARGET_NAME r-type_client)

include(CMakeSources.cmake)

add_executable(${TARGET_NAME} ${SOURCES})

file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/client)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/network)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/server/engine)

if (MSVC)
	add_compile_definitions(_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
else ()
	target_link_libraries(${TARGET_NAME} PRIVATE stdc++fs)
endif ()

target_link_libraries(${TARGET_NAME} PRIVATE ${CONAN_LIBS})
