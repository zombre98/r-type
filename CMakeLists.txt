cmake_minimum_required(VERSION 3.12)
project(r-type)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 17)

file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
include_directories(./lib/sol2)

add_subdirectory(lib/SFML)
add_subdirectory(src)
