// cubeGameTests.cpp
#include <gtest/gtest.h>

#include "cubeGame.hpp"

TEST(CubeGameTest, NullValidation) {}

int
main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}