cmake_minimum_required(VERSION 3.5)
project(calibrationDocSolver)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(calibrationDocSolver calibrationDocSolver.hpp calibrationDocSolverTests.cpp)
target_link_libraries(calibrationDocSolver ${GTEST_LIBRARIES} pthread)