cmake_minimum_required(VERSION 3.5)
project(calibrationDocSolver.a)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(calibrationDocSolver.a calibrationDocSolver.hpp calibrationDocSolverTests.cpp)
target_link_libraries(calibrationDocSolver.a ${GTEST_LIBRARIES} pthread)