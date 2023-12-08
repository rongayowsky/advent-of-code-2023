#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifndef CALIBRATION_DOC_SOLVER_H
#define CALIBRATION_DOC_SOLVER_H

class CalibrationDocParser {
   public:
    CalibrationDocParser(std::string &filepath) : m_filepath(filepath) {
        m_lines = readCalibrationLines();
    }
    std::vector<std::string> getCalibrationLines() { return m_lines; }

   private:
    std::vector<std::string> readCalibrationLines() {
        std::vector<std::string> lines;
        std::string line;
        std::ifstream myFile(m_filepath);

        if (myFile.is_open()) {
            while (getline(myFile, line)) {
                lines.push_back(line);
            }
            myFile.close();
        } else {
            std::cout << "Unable to open file" << std::endl;
        }

        return lines;
    }

   private:
    std::string m_filepath;
    std::vector<std::string> m_lines;
};

class CalibrationDocSolver {
   public:
    CalibrationDocSolver(std::vector<std::string> &calibrationDocLines)
        : m_calibrationDocLines(calibrationDocLines) {
        recoverCalibrationValsFromDoc();
    }

    uint16_t getCalibrationSum() {
        uint16_t sum{0};
        for (uint8_t &calibrationVal : m_calibrationVals) {
            sum += calibrationVal;
        }
        return sum;
    }

    std::vector<uint8_t> getCalibrationVals() { return m_calibrationVals; }

   private:
    std::vector<std::string> m_calibrationDocLines;
    std::vector<uint8_t> m_calibrationVals{};
    const int TENS_DIGIT_FACTOR{10};
    const int ONES_DIGIT_FACTOR{1};
    const char FIRST_ASCII_INT{'0'};

    void recoverCalibrationValsFromDoc() {
        for (std::string &line : m_calibrationDocLines) {
            std::pair<uint8_t, uint8_t> vals = getCalibrationValsFromLine(line);
            uint8_t val = vals.first * TENS_DIGIT_FACTOR +
                          vals.second * ONES_DIGIT_FACTOR;
            m_calibrationVals.push_back(val);
        }
    }

    std::pair<uint8_t, uint8_t> getCalibrationValsFromLine(std::string &line) {
        uint8_t firstDigit{0}, secondDigit{0};
        bool setFirst{false}, setSecond{false};
        for (int i{0}; i <= line.size(); ++i) {
            const char c1 = line[i];
            if (!setFirst && isInt(c1)) {
                firstDigit = toInt(c1);
                setFirst = true;
            }

            const char c2 = line[line.size() - i];
            if (!setSecond && isInt(c2)) {
                secondDigit = toInt(c2);
                setSecond = true;
            }

            if (setFirst && setSecond) {
                break;
            }
        }
        return std::pair<uint8_t, uint8_t>(firstDigit, secondDigit);
    }

    bool isInt(char c) {
        int val = c - FIRST_ASCII_INT;
        return (val >= 0 && val <= 9);
    }

    uint8_t toInt(char c) { return c - FIRST_ASCII_INT; }
};

#endif   // CALIBRATION_DOC_SOLVER_H
