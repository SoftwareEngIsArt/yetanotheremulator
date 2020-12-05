#include <iostream>

#include "core/register.hpp"

int main(int, char **)
{
    yae::core::Register<4> testReg("test");

    testReg.setOnModifyWatchpoint([](yae::core::IRegister &r) {
        std::cout << "new value = " << (size_t)r << std::endl;
    });

    int i = 0;
    //std::cin >> i;
    i = 1;
    testReg = i;

    testReg.rotateLeft();
    std::cout << "(size_t)testReg.rotateLeft() = " << (size_t)testReg << std::endl;
    testReg.rotateLeft();
    std::cout << "(size_t)testReg.rotateLeft() = " << (size_t)testReg << std::endl;
    testReg.rotateLeft();
    std::cout << "(size_t)testReg.rotateLeft() = " << (size_t)testReg << std::endl;
    testReg.rotateLeft();
    std::cout << "(size_t)testReg.rotateLeft() = " << (size_t)testReg << std::endl;
    testReg.rotateLeft();
    std::cout << "(size_t)testReg.rotateLeft() = " << (size_t)testReg << std::endl;
    testReg.rotateLeft();
    std::cout << "(size_t)testReg.rotateLeft() = " << (size_t)testReg << std::endl;

    return 0;
}