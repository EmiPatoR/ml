//
// Created by ehrustic on 05/04/18.
//

#ifndef ISAE_ML_TESTOBJ_HPP
#define ISAE_ML_TESTOBJ_HPP

#include <iostream>
#include <utility>

class TestObj {

private:
    int arg1;
    float arg2;
    std::string arg3;

public:
    TestObj(int arg1, float arg2, std::string arg3) : arg1(arg1), arg2(arg2), arg3(std::move(arg3)) {};

    int getArg1() { return arg1; }

    float getArg2() { return arg2; }

    std::string getArg3() { return arg3; }
};


#endif //ISAE_ML_TESTOBJ_HPP
