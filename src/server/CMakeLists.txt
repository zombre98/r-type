set(TARGET_NAME r-type_server)

include(CMakeSources.cmake)

add_executable(${TARGET_NAME} ${SOURCES} ${COMMON})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/common)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/server/library)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/server/engine)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/server/engine/systems)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/network)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/client)


if (MSVC)
	add_compile_definitions(_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
	# TODO(armandmgt) Define a macro to remove code related to library loading
else ()
	target_link_libraries(${TARGET_NAME} PRIVATE stdc++fs dl)
endif ()

target_link_libraries(${TARGET_NAME} PRIVATE ${CONAN_LIBS} lua)
