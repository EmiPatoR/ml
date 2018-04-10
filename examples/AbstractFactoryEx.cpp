//
// Created by ehrustic on 04/04/18.
//

#include <iostream>
#include <cassert>
#include <UTILS/AbstractFactory.hpp>
#include <memory>

class Test {
public:
    Test(int arg, int arg2) { std::cout << arg << "/" << arg2 << std::endl; }
};

int main(int argc, char *argv[]) {

    using TestFactory = ISAE_ML::UTILS::AbstractFactory<std::string, std::unique_ptr<Test>, int, int>;
    TestFactory testFactory;
    testFactory.Register("Test", [](int arg1, int arg2) { return std::unique_ptr<Test>(new Test(arg1, arg2)); });
    testFactory.Create("Test", 42, 55);
    return 0;
}
