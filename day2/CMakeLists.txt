cmake_minimum_required(VERSION 3.5)
project(cubeGame.a)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(cubeGame.a cubeGame.hpp cubeGameTests.cpp)
target_link_libraries(cubeGame.a ${GTEST_LIBRARIES} pthread)
