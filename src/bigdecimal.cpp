#include "bigdecimal.h"
#include <iostream>

//int constructor
BigDecimal::BigDecimal(int value, int precision) :  sign(value < 0), precision(precision), bits({}) {
    if (value == 0) {
        bits = {false};
    } else {
        int absValue = std::abs(value);
        while (absValue > 0) {
            if (absValue % 2 == 0) {
                bits.push_back(false);
            } else {
                bits.push_back(true);
            }
            absValue /= 2;
        }
        std::reverse(bits.begin(), bits.end());
        for (int i = 0; i < precision; i++) {
            bits.push_back(false);
        }
    }
    //normalize();
};

//double constructor
BigDecimal::BigDecimal(long double value, int precision) : sign(value < 0), precision(precision), bits({}) {
    if (value == 0) {
        bits = {false};
    } else {
        int absValue = std::abs(int(value));
        while (absValue > 0) {
            if (absValue % 2 == 0) {
                bits.push_back(false);
            } else {
                bits.push_back(true);
            }
            absValue /= 2;
        }
        std::reverse(bits.begin(), bits.end());
        long double fractional = value - int(value);

        for (int i = 0; i < precision; i++) {
            fractional *= 2;
            bits.push_back(int(fractional));
            fractional -= int(fractional);
        }
    }
    //normalize();
}

//utility function to divide string by 2 with remainder
int StringDel2(std::string &s) {
    int temp = 0;
    for (size_t i = 0; i < s.size(); i++) {
        temp = temp * 10 + (s[i] - '0');
        s[i] = temp / 2 + '0';
        temp %= 2;
    }
    return temp;
}

//utility function to multiply function by 2 with remainder?? kinda
int StringMul2(std::string &s) {
    int temp = 0;
    int last = 0;
    for (int i = s.size()-1; i >= 0; i--) {
        temp = (s[i] - '0') * 2 + last;
        s[i] = temp % 10 + '0';
        last = temp / 10;
    }
    return last;
}

//string checker
int isNull(std::string &s) {
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] != '0') {
            return 0;
        }
    }
    return 1;
}

//string constructor
BigDecimal::BigDecimal(std::string str, int precision) :  sign(str[0] == '-'), precision(precision), bits({}) {
    size_t dotPos = str.find('.');
    bool hasFractionalPart = dotPos != std::string::npos;
    std::string integerPartStr = str.substr(sign, dotPos - sign);
    std::string fractionalPartStr = hasFractionalPart ? str.substr(dotPos + 1) : "";

    bits = {};

    while (!isNull(integerPartStr)) {
        bits.push_back(StringDel2(integerPartStr));
    }
    std::reverse(bits.begin(), bits.end());

    for (int i = 0; i < precision; i++) {
        bits.push_back(StringMul2(fractionalPartStr));
    }
    //normalize();
}

//copy constructor
BigDecimal::BigDecimal(const BigDecimal &other) : sign(other.sign), precision(other.precision), bits(other.bits) {}

//destructor
BigDecimal::~BigDecimal() {}

//assignment operator
BigDecimal &BigDecimal::operator=(const BigDecimal &other) {
    if (this != &other) {
        bits = other.bits;
        precision = other.precision;
        sign = other.sign;
    }
    return *this;
}

//utility function that is actually useless
void BigDecimal::normalize() {
    std::vector<bool> temp = (*this).bits;
    std::reverse(temp.begin(), temp.end());
    for (size_t i = 0; i < (*this).bits.size() - (*this).precision - 1; i++) {
        if (temp[temp.size()-1] == false) {
            temp.pop_back();
        } else {
            break;
        }
    }
    std::reverse(temp.begin(), temp.end());
    (*this).bits = temp;
}

//utility function to align precision by another number
void BigDecimal::alignPrecision(const BigDecimal & other) {
    if (precision < other.precision) {
        int diff = other.precision - precision;
        for (int i = 0; i < diff; i++) {
            bits.push_back(false);
        }
        precision = other.precision;
    }
}

//equality operator
bool BigDecimal::operator==(const BigDecimal &other) const {
    if (sign != other.sign || bits.size() != other.bits.size()) return false;
    for (size_t i = 0; i < bits.size(); i++) {
        if (bits[i] != other.bits[i]) return false;
    }
    return true;
}

//non-equality operator
bool BigDecimal::operator!=(const BigDecimal &other) const {
    return !(*this == other);
}

//less operator
bool BigDecimal::operator<(const BigDecimal& other) const {
    if (sign && !other.sign) return true;
    if (!sign && other.sign) return false;

    BigDecimal a = *this;
    BigDecimal b = other;
    a.alignPrecision(b);

    int comparison = compareMagnitude(b);

    if (comparison < 0) {
        return !sign;
    } else if (comparison > 0) {
        return sign;
    } else {
        return false;
    }
}

int BigDecimal::compareMagnitude(const BigDecimal& other) const {
    if (bits.size() > other.bits.size()) return 1;
    if (bits.size() < other.bits.size()) return -1;

    for (size_t i = bits.size(); i > 0; --i) {
        if (bits[i - 1] > other.bits[i - 1]) return 1;
        if (bits[i - 1] < other.bits[i - 1]) return -1;
    }
    return 0;
}

//more operator
bool BigDecimal::operator>(const BigDecimal &other) const{
    return !(*this < other) && !(*this == other);
}

//literal suffix operator
BigDecimal operator""_longnum(long double number) {
    return BigDecimal(number, 128);
}

//function to turn number into string
std::string BigDecimal::toString() const {
    std::string result;
    if (sign) result += '-';
    for (size_t i = 0; i < bits.size(); i++) {
        result += std::to_string(bits[i]);
        if (i == bits.size() - precision - 1) result += '.';
    }
    return result;
}

void equalize(std::vector<bool> *x, std::vector<bool> *y, int x_precision, int y_precision) {
    for (int i = 0; i < x_precision - y_precision; i++) { //x_precision > y_precision
        (*y).push_back(false);
    }
    for (int i = 0; i < y_precision - x_precision; i++) { //y_precision > x_precision
        (*x).push_back(false);
    }
    std::reverse((*x).begin(), (*x).end());
    std::reverse((*y).begin(), (*y).end());

    while ((*x).size() > (*y).size()) { //x.size > y.size
        (*y).push_back(false);
    }
    while ((*x).size() < (*y).size()) { //y.size > x.size
        (*x).push_back(false);
    }
}

//binary vector absolute sum
std::vector<bool> absolute_plus(std::vector<bool> x, std::vector<bool> y) {
    std::vector <bool> new_bits;
    int last = 0;
    int temp = 0;

    for (size_t i = 0 ; i < x.size(); i++) {
        temp = last + x[i] + y[i];
        last = temp / 2;
        new_bits.push_back(temp % 2);
    }
    if (last == 1) {
        new_bits.push_back(true);
    }
    std::reverse(new_bits.begin(), new_bits.end());
    return new_bits;
}

//binary vector absolute dif
std::vector<bool> absolute_minus(std::vector<bool> x, std::vector<bool> y) {
    std::vector<bool> new_bits;
    int borrow = 0;
    int temp = 0;

    for (size_t i = 0; i < x.size(); i++) {
        if (borrow == 1) {
            if (x[i] == 0) {
                temp = 1;
                borrow = 1;
            } else {
                temp = 0;
                borrow = 0;
            }
        }
        else {
            temp = x[i];
        }
        if (temp == 0 && y[i] == 1) {
            temp = 1;
            borrow = 1;
        } else {
            temp -= y[i];
        }
        new_bits.push_back(temp);
    }

    std::reverse(new_bits.begin(), new_bits.end());
    return new_bits;
}

//plus operator
BigDecimal BigDecimal::operator+(const BigDecimal &other) const {
    std::vector<bool> a_bits = (*this).bits;
    std::vector<bool> b_bits = other.bits;

    equalize(&a_bits, &b_bits, (*this).precision, other.precision);

    BigDecimal result(0, std::max((*this).precision, other.precision));
    if ((*this).sign == other.sign) {
        result.bits = absolute_plus(a_bits, b_bits);
        result.sign = (*this).sign;
    } else {
        BigDecimal temp = other;
        temp.sign = 1 - temp.sign;
        return (*this) - temp;
    }

    return result;
}

//minus operator
BigDecimal BigDecimal::operator-(const BigDecimal& other) const {
    std::vector<bool> a_bits = (*this).bits;
    std::vector<bool> b_bits = other.bits;

    equalize(&a_bits, &b_bits, (*this).precision, other.precision);
    BigDecimal result(0, std::max((*this).precision, other.precision));
    if ((*this).sign == other.sign) {
        if (compareMagnitude(other) >= 0) {
            result.bits = absolute_minus(a_bits, b_bits);
            result.sign = (*this).sign;
        } else {
            result.bits = absolute_minus(b_bits, a_bits);
            result.sign = !(*this).sign;
        }
    }
    else {
        result.bits = absolute_plus(a_bits, b_bits);
        result.sign = (*this).sign;
    }
    result.normalize();
    return result;
}

//multiply operator
BigDecimal BigDecimal::operator*(const BigDecimal& other) const {
    BigDecimal temp = other;
    temp.sign = 0;
    temp.precision = precision + other.precision;
    BigDecimal result (0,0);
    std::vector<bool> trail = bits;
    std::reverse(trail.begin(), trail.end());
    for (size_t i = 0; i < trail.size(); i++) {
        result = result + temp;
        temp.precision--;
        std::cout << result.toString() << std::endl;
    }
    result.precision = precision + other.precision;
    result.sign = (sign != other.sign);
    return result;
}
