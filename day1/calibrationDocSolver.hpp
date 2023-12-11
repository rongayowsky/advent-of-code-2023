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

/*
now we need to detect spelled numbers as well. can grab handfill of chars in
buckets of 3, 4, and 5 chunks, optionally reverse the spelling, and check a
hashmap for the match.

one two three four five six seven eight nine.

early exit condition, only check first letter to see if in list before string
matching:

starting letters:
o t f s e n

ending numbers:
e o r x n t
*/

class CalibrationDocSolver {
   public:
    CalibrationDocSolver(std::vector<std::string> &calibrationDocLines,
                         bool matchSpelledNumbers = false)
        : m_calibrationDocLines(calibrationDocLines),
          M_MATCH_SPELLED_NUMBERS(matchSpelledNumbers) {
        recoverCalibrationValsFromDoc();
    }

    int getCalibrationSum() {
        int sum{0};
        for (int &calibrationVal : m_calibrationVals) {
            sum += calibrationVal;
        }
        return sum;
    }

    std::vector<int> getCalibrationVals() { return m_calibrationVals; }

   private:
    std::vector<std::string> m_calibrationDocLines;
    std::vector<int> m_calibrationVals{};
    const int M_TENS_DIGIT_FACTOR{10};
    const int M_ONES_DIGIT_FACTOR{1};
    const char M_FIRST_ASCII_INT{'0'};
    bool M_MATCH_SPELLED_NUMBERS;
    std::map<std::string, int> SPELLED_NUMBERS = {
        {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
        {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
    };

    // used for reduction of rudundant checks
    const std::string STARTING_CHARS = "otfsen";
    const std::string ENDING_CHARS = "eorxnt";
    const int MAX_WORD_LENGTH = 5;

    void recoverCalibrationValsFromDoc() {
        int i = 0;
        for (std::string &line : m_calibrationDocLines) {
            std::pair<int, int> vals = getCalibrationValsFromLine(line);
            int val = vals.first * M_TENS_DIGIT_FACTOR +
                      vals.second * M_ONES_DIGIT_FACTOR;
            m_calibrationVals.push_back(val);
        }
    }

    std::pair<int, int> getCalibrationValsFromLine(std::string &line) {
        int firstDigit{0}, secondDigit{0};
        bool setFirst{false}, setSecond{false};
        for (int i{0}; i <= line.size(); ++i) {
            const char c1 = line[i];
            if (!setFirst && isInt(c1)) {
                firstDigit = toInt(c1);
                setFirst = true;
            } else if (M_MATCH_SPELLED_NUMBERS && !setFirst) {
                int value = matchSpelledNumberLeftToRight(line, i);
                if (value >= 0) {
                    firstDigit = value;
                    setFirst = true;
                }
            }

            const char c2 = line[line.size() - i];
            if (!setSecond && isInt(c2)) {
                secondDigit = toInt(c2);
                setSecond = true;
            } else if (M_MATCH_SPELLED_NUMBERS && !setSecond) {
                int value =
                    matchSpelledNumberRightToLeft(line, line.size() - i);
                if (value >= 0) {
                    secondDigit = value;
                    setSecond = true;
                }
            }

            if (setFirst && setSecond) {
                break;
            }
        }
        return std::pair<int, int>(firstDigit, secondDigit);
    }

    int matchSpelledNumberLeftToRight(std::string &line, int index) {
        // Early exit if char is not a beginning character of 1-9
        if (STARTING_CHARS.find(line[index]) == std::string::npos) {
            return -1;
        }
        return matchSpelledNumber(line.substr(index, MAX_WORD_LENGTH));
    }

    int matchSpelledNumberRightToLeft(std::string &line, int index) {
        // Early exit if char is not an ending character of 1-9
        // NOTE: there be a bug that is trigger when this optimization is used.
        // See test SpelledNumberTrickyExampleValidation.
        // if (ENDING_CHARS.find(line[index]) == std::string::npos) {
        //     return -1;
        // }

        int saneIndex{index - MAX_WORD_LENGTH + 1};
        int lengthReduction{0};
        if (saneIndex < 0) {
            saneIndex = 0;
            lengthReduction = index - MAX_WORD_LENGTH + 1;
        }
        return matchSpelledNumber(
            line.substr(saneIndex, MAX_WORD_LENGTH + 1 + lengthReduction),
            false);
    }

    int matchSpelledNumber(const std::string subString,
                           const bool isLeftToRight = true) {
        int value{-1};

        // Try to match character to spelled number
        for (int length{3}; length <= 5; ++length) {
            if (isLeftToRight && SPELLED_NUMBERS.find(subString.substr(
                                     0, length)) != SPELLED_NUMBERS.end()) {
                value = SPELLED_NUMBERS.at(subString.substr(0, length));
                break;
            } else if (!isLeftToRight &&
                       SPELLED_NUMBERS.find(subString.substr(
                           MAX_WORD_LENGTH - length, length)) !=
                           SPELLED_NUMBERS.end()) {
                value = SPELLED_NUMBERS.at(
                    subString.substr(MAX_WORD_LENGTH - length, length));
                break;
            }
        }
        return value;
    }

    bool isInt(char c) {
        int val = c - M_FIRST_ASCII_INT;
        return (val >= 0 && val <= 9);
    }

    // Look up ASCII character mapping to understand how this subtraction leads
    // to the numerical value: https://www.asciitable.com/
    int toInt(char c) { return c - M_FIRST_ASCII_INT; }
};

#endif   // CALIBRATION_DOC_SOLVER_H
