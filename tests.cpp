#include "bigdecimal.h"
#include <iostream>

bool testAddition() {
    BigDecimal a ("10.5", 128);
    BigDecimal b ("3.25", 128);
    BigDecimal result = a + b;
    BigDecimal expected ("13.75", 128);
    return result == expected;
}

bool testSubscription() {
    BigDecimal a ("0.5", 128);
    BigDecimal b ("3.25", 128);
    BigDecimal result = a + b;
    BigDecimal expected ("-2.75", 128);
    std::cout << result.toString() << std::endl;
    std::cout << expected.toString() << std::endl;
    return result == expected;
}

void runTest(char* message, bool result) {
    std::cout << message;
    if (result) {
        std::cout << "OK";
    } else {
        std::cout << "FAIL";
    }
    std::cout << std::endl;
}

int main() {
    runTest("test addiction: ", testAddition());
    runTest("test subscription: ", testSubscription());
    return 0;
}