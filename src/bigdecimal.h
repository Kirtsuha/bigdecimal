#pragma once

#ifndef BIGDECIMAL_H
#define BIGDECIMAL_H

#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

class BigDecimal {
private:
    bool sign = false;        
    int precision;             
    std::vector<bool> bits; 

public:
    BigDecimal(int value = 0, int precision = 0);
    BigDecimal(long double value, int precision);
    BigDecimal(std::string value, int precision);

    BigDecimal(long double value);
    BigDecimal(std::string value);
    
    BigDecimal(const BigDecimal& other);
    ~BigDecimal();

    BigDecimal& operator=(const BigDecimal& other);

    bool operator==(const BigDecimal & other) const;
    bool operator!=(const BigDecimal & other) const;
    bool operator<(const BigDecimal & other) const;
    bool operator>(const BigDecimal & other) const;

    BigDecimal operator+(const BigDecimal & other) const;
    BigDecimal operator-(const BigDecimal & other) const;
    BigDecimal operator*(const BigDecimal & other) const;
    BigDecimal operator/(const BigDecimal & other) const;

    int compareMagnitude(const BigDecimal& other) const;
    void setPrecision(int newPrecision);
    void normalize();
    void alignPrecision(const BigDecimal & other);

    std::string toString() const;
    long double toDouble() const;
};

BigDecimal operator""_longnum(long double number);

#endif //BIGDECIMAL_H
