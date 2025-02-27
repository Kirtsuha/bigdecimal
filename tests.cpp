#include "bigdecimal.h"
#include <iostream>

bool testAddition() {
    BigDecimal a ("10.5", 128);
    BigDecimal b ("3.25", 128);
    BigDecimal result = a + b;
    BigDecimal expected ("13.75", 128);
    return result == expected;
}

int main() {
    bool add = testAddition();
    std::cout << "testAddition: ";
    if (add) {std::cout << "OK";}
    else {std::cout << "FAIL";}
    std::cout << std::endl;
}