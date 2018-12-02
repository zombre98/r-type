cmake_minimum_required(VERSION 3.10)
project(r-type)

set(CONAN_CMAKE_VER v0.13)
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan-${CONAN_CMAKE_VER}.cmake")
	message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
	file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/${CONAN_CMAKE_VER}/conan.cmake"
		"${CMAKE_BINARY_DIR}/conan-${CONAN_CMAKE_VER}.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan-${CONAN_CMAKE_VER}.cmake)

if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    set(CONAN_EXPORTED)
    set(CMAKE_BUILD_TYPE Debug)
endif()

conan_cmake_run(CONANFILE conanfile.txt
                BASIC_SETUP NO_OUTPUT_DIRS)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib/sol2)

add_subdirectory(lib/lua)
add_subdirectory(src)
