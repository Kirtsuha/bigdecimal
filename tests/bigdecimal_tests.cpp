//#include "../src/bigdecimal.h"
#include "../src/bigdecimal.h"
#include <iostream>
#include <string>
#include <cassert>

void test_addition() {
    BigDecimal a (10, 128);
    BigDecimal b ("3.75", 128);
    BigDecimal result = a + b;
    BigDecimal expected ("13.75", 128);
    assert(result == expected);
    std::cout << "test_addition: OK" << std::endl;
}

void test_subscription() {
    BigDecimal a = 0.5_longnum;
    BigDecimal b = 3.25_longnum;
    BigDecimal result = a - b;
    BigDecimal expected ("-2.75", 128);
    assert(result == expected);
    std::cout << "test_subscription: OK" << std::endl;
}

void test_equal() {
    BigDecimal a ("133.55", 128);
    BigDecimal b ("133.55", 128);
    assert(a == b);
    std::cout << "test_equal: OK" << std::endl;
}

void test_larger() {
    BigDecimal a (133, 0);
    BigDecimal b ("-234.31", 1);
    assert(a > b);
    std::cout << "test_larger: OK" << std::endl; 
}

void test_lower() {
    BigDecimal a ("133.55", 128);
    BigDecimal b ("133.5500000000000000001");
    assert(a < b);
    std::cout << "test_lower: OK" << std::endl;
}

void test_multiply() {
    BigDecimal a ("0.1875", 15);
    BigDecimal b ("0.25", 5);
    BigDecimal check ("0.046875", 20);
    assert(a*b == check);
    std::cout << "test_multiply: OK" << std::endl;
}

void test_divide() {
    BigDecimal a ("123", 4);
    BigDecimal d ("3", 7);
    BigDecimal z = a/d;
    
    BigDecimal check ("41");
    assert(z == check);
    std::cout << "test_divide: OK" << std::endl;
}


int main() {
    test_addition();
    test_subscription();
    test_equal();
    test_larger();
    test_lower();
    test_multiply();
    test_divide();
    return 0;
}