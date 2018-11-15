cmake_minimum_required(VERSION 3.12)
project(r-type)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${PROJECT_NAME}/src/network)
#add_subdirectory(lib/SFML)
add_subdirectory(src)
