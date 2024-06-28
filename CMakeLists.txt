cmake_minimum_required(VERSION 3.0)
project(programming0)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -g")
endif()

add_executable(tests tests.cpp)
add_executable(msf  msf.cpp)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extra_tests.cpp)
    add_executable(extra_tests extra_tests.cpp)
endif()