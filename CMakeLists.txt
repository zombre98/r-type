cmake_minimum_required(VERSION 3.12)
project(r-type)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
	message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
	file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.13/conan.cmake"
		"${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

if(NOT EXISTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/conanbuildinfo.cmake)
    conan_cmake_run(CONANFILE conanfile.txt
                    BASIC_SETUP)
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(lib/sol2)

add_subdirectory(lib/lua)
add_subdirectory(src)
