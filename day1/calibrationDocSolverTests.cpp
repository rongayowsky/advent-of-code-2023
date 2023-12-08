// calibrationDocSolverTest.cpp
#include <gtest/gtest.h>

#include "calibrationDocSolver.hpp"

TEST(CalibrationDocSolverTest, NullValidation) {
    std::vector<std::string> calibrationDoc{};
    CalibrationDocSolver solver{calibrationDoc};
    ASSERT_EQ(solver.getCalibrationSum(), 0);
    ASSERT_EQ(solver.getCalibrationVals().size(), 0);
}

TEST(CalibrationDocSolverTest, NoWorkValidation) {
    std::vector<std::string> calibrationDoc{};
    calibrationDoc.push_back("12");

    CalibrationDocSolver solver{calibrationDoc};
    ASSERT_EQ(solver.getCalibrationSum(), 12);
    ASSERT_EQ(solver.getCalibrationVals().size(), 1);
}

TEST(CalibrationDocSolverTest, SingleNumberValidation) {
    std::vector<std::string> calibrationDoc{};
    calibrationDoc.push_back("1");

    CalibrationDocSolver solver{calibrationDoc};
    ASSERT_EQ(solver.getCalibrationSum(), 11);
    ASSERT_EQ(solver.getCalibrationVals().size(), 1);
}

TEST(CalibrationDocSolverTest, exampleValidation) {
    std::vector<std::string> calibrationDoc{};
    calibrationDoc.push_back("1abc2");
    calibrationDoc.push_back("pqr3stu8vwx");
    calibrationDoc.push_back("a1b2c3d4e5f");
    calibrationDoc.push_back("treb7uchet");

    CalibrationDocSolver solver{calibrationDoc};
    ASSERT_EQ(solver.getCalibrationSum(), 142);
    ASSERT_EQ(solver.getCalibrationVals().size(), 4);
}

TEST(CalibrationDocSolverTest, fullSumOfCalibrationValues) {
    std::string filepath = "calibrationDoc.txt";
    CalibrationDocParser parser{filepath};
    std::vector<std::string> calibrationDoc{parser.getCalibrationLines()};

    CalibrationDocSolver solver{calibrationDoc};
    std::cout << "sum = " << solver.getCalibrationSum() << std::endl;
}

int
main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}