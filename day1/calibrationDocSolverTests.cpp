// calibrationDocSolverTest.cpp
#include <gtest/gtest.h>

#include "calibrationDocSolver.hpp"

TEST(CalibrationDocSolverTest, NullValidation) {
    std::vector<std::string> calibrationDoc{};
    CalibrationDocSolver solver{calibrationDoc};
    ASSERT_EQ(solver.getCalibrationSum(), 0);
    ASSERT_EQ(solver.getCalibrationVals().size(), 0);
}

TEST(CalibrationDocSolverTest, SpelledNumberNullValidation) {
    std::vector<std::string> calibrationDoc{};
    CalibrationDocSolver solver{calibrationDoc, true};
    ASSERT_EQ(solver.getCalibrationSum(), 0);
    ASSERT_EQ(solver.getCalibrationVals().size(), 0);
}

TEST(CalibrationDocSolverTest, MinimalWorkValidation) {
    std::vector<std::string> calibrationDoc{};
    calibrationDoc.push_back("12");

    CalibrationDocSolver solver{calibrationDoc};
    ASSERT_EQ(solver.getCalibrationSum(), 12);
    ASSERT_EQ(solver.getCalibrationVals().size(), 1);
}

TEST(CalibrationDocSolverTest, SpelledNumberMinimalWorkValidation) {
    std::vector<std::string> calibrationDoc{};
    calibrationDoc.push_back("onetwo");

    CalibrationDocSolver solver{calibrationDoc, true};
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

TEST(CalibrationDocSolverTest, SpelledNumberSingleValidation) {
    std::vector<std::string> calibrationDoc{};
    calibrationDoc.push_back("one");

    CalibrationDocSolver solver{calibrationDoc, true};
    ASSERT_EQ(solver.getCalibrationSum(), 11);
    ASSERT_EQ(solver.getCalibrationVals().size(), 1);
}

TEST(CalibrationDocSolverTest, SpelledNumberOneLineValidation) {
    std::vector<std::string> calibrationDoc{};
    calibrationDoc.push_back("asdfonetwothree4five");

    CalibrationDocSolver solver{calibrationDoc, true};
    ASSERT_EQ(solver.getCalibrationSum(), 15);
    ASSERT_EQ(solver.getCalibrationVals().size(), 1);
}

TEST(CalibrationDocSolverTest, ExampleValidation) {
    std::vector<std::string> calibrationDoc{};
    calibrationDoc.push_back("1abc2");
    calibrationDoc.push_back("pqr3stu8vwx");
    calibrationDoc.push_back("a1b2c3d4e5f");
    calibrationDoc.push_back("treb7uchet");

    CalibrationDocSolver solver{calibrationDoc};
    ASSERT_EQ(solver.getCalibrationSum(), 142);
    ASSERT_EQ(solver.getCalibrationVals().size(), 4);
}

TEST(CalibrationDocSolverTest, SpelledNumberExampleValidation) {
    std::vector<std::string> calibrationDoc{};
    calibrationDoc.push_back("two1nine");
    calibrationDoc.push_back("eightwothree");
    calibrationDoc.push_back("abcone2threexyz");
    calibrationDoc.push_back("xtwone3four");
    calibrationDoc.push_back("4nineeightseven2");
    calibrationDoc.push_back("zoneight234");
    calibrationDoc.push_back("7pqrstsixteen");

    CalibrationDocSolver solver{calibrationDoc, true};
    ASSERT_EQ(solver.getCalibrationSum(), 281);
    ASSERT_EQ(solver.getCalibrationVals().size(), 7);
}

TEST(CalibrationDocSolverTest, SpelledNumberTrickyExampleValidation) {
    std::vector<std::string> calibrationDoc{};
    calibrationDoc.push_back("eighthree");
    calibrationDoc.push_back("sevenine");
    calibrationDoc.push_back("abc2x3oneight");
    calibrationDoc.push_back("7sixjhhzhgh");

    CalibrationDocSolver solver{calibrationDoc, true};
    ASSERT_EQ(solver.getCalibrationSum(), 83 + 79 + 28 + 76);
    ASSERT_EQ(solver.getCalibrationVals().size(), 4);
}

TEST(CalibrationDocSolverTest, SpelledNumberMapValidation) {
    std::vector<std::string> calibrationDoc{};
    calibrationDoc.push_back("one");
    calibrationDoc.push_back("two");
    calibrationDoc.push_back("three");
    calibrationDoc.push_back("four");
    calibrationDoc.push_back("five");
    calibrationDoc.push_back("six");
    calibrationDoc.push_back("seven");
    calibrationDoc.push_back("eight");
    calibrationDoc.push_back("nine");

    CalibrationDocSolver solver{calibrationDoc, true};
    ASSERT_EQ(solver.getCalibrationSum(),
              11 + 22 + 33 + 44 + 55 + 66 + 77 + 88 + 99);
    ASSERT_EQ(solver.getCalibrationVals().size(), 9);
}

TEST(CalibrationDocSolverTest, FullSumOfCalibrationValues) {
    std::string filepath = "input.txt";
    CalibrationDocParser parser{filepath};
    std::vector<std::string> calibrationDoc{parser.getCalibrationLines()};

    CalibrationDocSolver solver{calibrationDoc};
    std::cout << "sum = " << solver.getCalibrationSum() << std::endl;
    ASSERT_EQ(solver.getCalibrationSum(), 56042);   // verified answer
}

TEST(CalibrationDocSolverTest, SpelledNumberFullSumOfCalibrationValues) {
    std::string filepath = "input.txt";
    CalibrationDocParser parser{filepath};
    std::vector<std::string> calibrationDoc{parser.getCalibrationLines()};

    CalibrationDocSolver solver{calibrationDoc, true};
    std::cout << "sum = " << solver.getCalibrationSum() << std::endl;
    ASSERT_EQ(solver.getCalibrationSum(), 55358);   // verified answer
}

int
main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}