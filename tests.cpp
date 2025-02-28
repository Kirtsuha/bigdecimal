#include "bigdecimal.h"
#include <iostream>
#include <string>

bool testAddition() {
    BigDecimal a (10, 128);
    BigDecimal b ("3.75", 128);
    BigDecimal result = a + b;
    BigDecimal expected ("13.75", 128);
    return result == expected;
}

bool testSubscription() {
    BigDecimal a = 0.5_longnum;
    BigDecimal b = 3.25_longnum;
    BigDecimal result = a - b;
    BigDecimal expected ("-2.75", 128);
    return result == expected;
}

bool testIsEqual() {
    BigDecimal a ("133.55", 128);
    BigDecimal b ("133.55", 128);
    return a == b;
}

bool testIsLarger() {
    BigDecimal a ("133.55", 128);
    BigDecimal b ("-23423413.5123125", 128);
    return a > b;
}

bool testIsLower() {
    BigDecimal a ("133.55", 128);
    BigDecimal b ("133.55001", 128);
    return a < b;
}

bool testMultiply() {
    BigDecimal a ("6.25", 2);
    BigDecimal b("0.75", 2);
    BigDecimal result = a * b;
    return 1;
}

void runTest(std::string message, bool result) {
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
    runTest("test equalisation: ", testIsEqual());
    runTest("test larger: ", testIsLarger());
    runTest("test lower: ", testIsLower());
    testMultiply() ;
    return 0;
}