#include "bigdecimal.h"
#include <iostream>
#include <string>
#include "gtest/gtest.h"

TEST(BigDecimalTest, Addition) {
    BigDecimal a (10, 128);
    BigDecimal b ("3.75", 128);
    BigDecimal result = a + b;
    BigDecimal expected ("13.75", 128);
    EXPECT_EQ(result, expected);
}

TEST(BigDecimalTest, Subscription) {
    BigDecimal a = 0.5_longnum;
    BigDecimal b = 3.25_longnum;
    BigDecimal result = a - b;
    BigDecimal expected ("-2.75", 128);
    EXPECT_EQ(result, expected);
}

TEST(BigDecimalTest, Equal) {
    BigDecimal a ("133.55", 128);
    BigDecimal b ("133.55", 128);
    EXPECT_EQ(a == b, 1);
}

TEST(BigDecimalTest, Larger) {
    BigDecimal a (133, 0);
    BigDecimal b ("-234.31", 1);
    EXPECT_EQ(a > b, 1); //check
}

TEST(BigDecimalTest, Lower) {
    BigDecimal a ("133.55", 128);
    BigDecimal b ("133.55001", 128);
    EXPECT_EQ(a < b, 1);
}

/*TEST(BigDecimalTest, Multiply) {
    BigDecimal a ("6.25", 2);
    BigDecimal b("0.75", 2);
    BigDecimal result = a * b;
    return 1;
}*/

/*void runTest(std::string message, bool result) {
    std::cout << message;
    if (result) {
        std::cout << "OK";
    } else {
        std::cout << "FAIL";
    }
    std::cout << std::endl;
}
int main() {
    std::cout << "OK!!!";
    return 0;
}*/