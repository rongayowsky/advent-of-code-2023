//
// Taken from https://github.com/raleighlittles/Minimal-GTest-Example
//
#include <iostream>

#ifndef GTEST_EXAMPLE_FAKE_CLASS_H
#define GTEST_EXAMPLE_FAKE_CLASS_H


class fake_class {

public:
    fake_class()
    {
        std::cout << "Fake class created" << std::endl;
    }

    int add_numbers(int n1, int n2)
    {
        return (n1 + n2);
    }

    int subtract_numbers(int n1, int n2)
    {
        return (n1 - n2);
    }

};


#endif //GTEST_EXAMPLE_FAKE_CLASS_H
