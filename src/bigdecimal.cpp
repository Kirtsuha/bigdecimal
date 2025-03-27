#include "bigdecimal.h"
#include <iostream>

//int constructor
BigDecimal::BigDecimal(int value, int precision) :  sign(value < 0), precision(precision) {
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
BigDecimal::BigDecimal(long double value, int precision) : sign(value < 0), precision(precision) {
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

//double constructor, no precision
BigDecimal::BigDecimal(long double value) : sign(value < 0), precision(0) {
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
        precision = 0;
        int fract_length = 0;
        long double fract_copy = fractional;

        while (fractional > 0) {
            fract_length++;
            fract_copy *= 10;
        }
        if (fractional > 0) {
            precision = static_cast<int>(std::ceil(fract_length* std::log2(10)));
        }

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
BigDecimal::BigDecimal(std::string str, int precision) :  sign(str[0] == '-'), precision(precision) {
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


//string constructor, no precision
BigDecimal::BigDecimal(std::string str) : sign(str[0] == '-'), precision(0) {
    size_t dotPos = str.find('.');
    bool hasFractionalPart = dotPos != std::string::npos;
    std::string integerPartStr = str.substr(sign, dotPos - sign);
    std::string fractionalPartStr = hasFractionalPart ? str.substr(dotPos + 1) : "";

    bits = {};

    while (!isNull(integerPartStr)) {
        bits.push_back(StringDel2(integerPartStr));
    }
    std::reverse(bits.begin(), bits.end());
    
    precision = 0;
    if (hasFractionalPart) {
        precision = static_cast<int>(std::ceil(fractionalPartStr.size() * std::log2(10)));
    }
    //precision = 4; ///!!!!!!!!!!!!!!!!!!!!DELETE

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
    // Разделяем биты на целую и дробную части
    size_t integerPartSize = bits.size() > precision ? bits.size() - precision : 0;
    size_t fractionalPartSize = precision;

    // Удаляем ведущие нули в целой части
    size_t firstNonZeroIndex = 0;
    while (firstNonZeroIndex < integerPartSize && bits[firstNonZeroIndex] == false) {
        firstNonZeroIndex++;
    }

    // Если все биты в целой части нулевые, оставляем один ноль
    if (firstNonZeroIndex == integerPartSize) {
        firstNonZeroIndex = integerPartSize - 1; // Оставляем один ноль
    }

    // Создаем новый вектор битов, начиная с первого ненулевого бита
    std::vector<bool> normalizedBits;
    for (size_t i = firstNonZeroIndex; i < bits.size(); i++) {
        normalizedBits.push_back(bits[i]);
    }

    // Если все биты были удалены (число стало нулём), добавляем один нулевой бит
    if (normalizedBits.empty()) {
        normalizedBits.push_back(false);
        sign = false; // Ноль всегда положителен
    }
    bool isnull = true;
    for (size_t i = 0; i < normalizedBits.size(); i++) {
        if (normalizedBits[i]) {
            isnull = false;
        }
    }
    if (isnull) {
        sign = false;
    }

    // Обновляем биты объекта
    bits = normalizedBits;
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
    BigDecimal left = (*this);
    BigDecimal right = other;
    left.alignPrecision(right);
    right.alignPrecision(left);

    if (left.sign != right.sign || left.bits.size() != right.bits.size()) return false;
    for (size_t i = 0; i < left.bits.size(); i++) {
        if (left.bits[i] != right.bits[i]) return false;
    }
    return true;
}

//non-equality operator
bool BigDecimal::operator!=(const BigDecimal &other) const {
    return !(*this == other);
}


int BigDecimal::compareMagnitude(const BigDecimal& other) const {
    std::vector<bool> left = bits;
    std::vector<bool> right = other.bits;
    
    if (left.size() > right.size()) return 1;
    if (left.size() < right.size()) return -1;

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for (size_t i = 0; i < left.size(); i++) {
        if (left[i] > right[i]) return 1;
        if (left[i] < right[i]) return -1;
    }
    return 0;
}

void BigDecimal::simplify() {
    while (bits[bits.size()-1] == false) {
        bits.pop_back();
        precision--;
    }
}

//less operator
bool BigDecimal::operator<(const BigDecimal& other) const {
    if (sign && !other.sign) return true;
    if (!sign && other.sign) return false;

    BigDecimal a = *this;
    BigDecimal b = other;
    a.alignPrecision(b);
    b.alignPrecision(a);

    int comparison = a.compareMagnitude(b);

    if (comparison < 0) {
        return !sign;
    } else if (comparison > 0) {
        return sign;
    } else {
        return false;
    }
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
long double BigDecimal::toDouble() const {
    long double ans = 0;
    long double two = pow(2, bits.size() - precision - 1);
    for (int i = 0; i < bits.size(); i++) {
        ans += bits[i] * two;
        two /= 2;
    }
    if (sign) {
        ans *= -1;
    }
    return ans;
}
/*
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
*/

//binary vector absolute sum
std::vector<bool> absolute_plus(std::vector<bool> x, std::vector<bool> y) {
    std::vector <bool> new_bits;

    std::vector <bool> a = x;
    std::vector <bool> b = y;
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    while (a.size() < b.size()) {
        a.push_back(false);
    }
    while (b.size() < a.size()) {
        b.push_back(false);
    }

    int last = 0;
    int temp = 0;

    for (size_t i = 0 ; i < a.size(); i++) {
        temp = last + a[i] + b[i];
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
    

    std::vector <bool> a = x;
    std::vector <bool> b = y;

    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());

    while (a.size() < b.size()) {
        a.push_back(false);
    }

    while (b.size() < a.size()) {
        b.push_back(false);
    }
    

    for (size_t i = 0; i < a.size(); i++) {
        if (borrow == 1) {
            if (a[i] == 0) {
                temp = 1;
                borrow = 1;
            } else {
                temp = 0;
                borrow = 0;
            }
        }
        else {
            temp = a[i];
        }
        if (temp == 0 && b[i] == 1) {
            temp = 1;
            borrow = 1;
        } else {
            temp -= b[i];
        }
        new_bits.push_back(temp);
    }

    std::reverse(new_bits.begin(), new_bits.end());
    /*std::cout << "(";
    for (size_t i = 0; i < new_bits.size(); i++) {
        std::cout << new_bits[i];
    } 
    std::cout << ")" << std::endl;*/
    return new_bits;
}

//plus operator
BigDecimal BigDecimal::operator+(const BigDecimal &other) const {
    BigDecimal a = (*this);
    BigDecimal b = other;
    a.alignPrecision(b);
    b.alignPrecision(a);

    BigDecimal result(0, a.precision);
    if ((*this).sign == other.sign) {
        result.bits = absolute_plus(a.bits, b.bits);
        result.sign = (*this).sign;
    } else {
        b.sign = 1 - b.sign;
        return a - b;
    }
    result.normalize();
    return result;
}

//minus operator
BigDecimal BigDecimal::operator-(const BigDecimal& other) const {
    BigDecimal a = (*this);
    BigDecimal b = other;
    a.alignPrecision(b);
    b.alignPrecision(a);

    /*std::vector<bool> a_bits = (*this).bits;
    std::vector<bool> b_bits = other.bits;
    equalize(&a_bits, &b_bits, (*this).precision, other.precision);*/

    BigDecimal result(0, a.precision);
    if ((*this).sign == other.sign) {
        if (compareMagnitude(other) >= 0) {
            result.bits = absolute_minus(a.bits, b.bits);
            result.sign = (*this).sign;
            
        } else {
            result.bits = absolute_minus(b.bits, a.bits);
            result.sign = !(*this).sign;
        }
    }
    else {
        result.bits = absolute_plus(a.bits, b.bits);
        result.sign = b.sign;
    }
    result.normalize();
    return result;
}

//multiply operator
BigDecimal BigDecimal::operator*(const BigDecimal& other) const {
    BigDecimal temp;
    temp.bits = other.bits;
    temp.sign = 0;
    temp.precision = 0;

    BigDecimal result(0, 0);

    std::vector<bool> trail = (*this).bits;
    std::reverse(trail.begin(), trail.end());
    //std::cout << "temp: " << temp.toString() << std::endl;

    for (size_t i = 0; i < trail.size(); i++) {
        if (trail[i]) {
            result = result + temp;
        }
        temp.bits.push_back(false);
        //std::cout << i << " | " << temp.toString() << ": " << result.toString() << std::endl;
    }

    result.precision = (*this).precision + other.precision;

    if (result.bits.size() < size_t(result.precision)) {
        std::reverse(result.bits.begin(), result.bits.end());
        while (result.bits.size() < size_t(result.precision)) {
            result.bits.push_back(false);
        }
        std::reverse(result.bits.begin(), result.bits.end());
    }
    result.sign = ((*this).sign != other.sign);

    return result;
}

//divide operation
BigDecimal BigDecimal::operator/(const BigDecimal& other) const {
    // Проверка деления на ноль
    if (other == BigDecimal("0")) {
        throw std::runtime_error("Division by zero");
    }
    BigDecimal divisor = other;
    divisor.precision = 0;
    BigDecimal divided = *this;
    divided.precision = precision;
    for (int i = 0; i < other.precision; i++) {
        divisor.bits.push_back(false);
        divided.bits.push_back(false);
    }

    divisor.sign = false;
    divided.sign = false;

    BigDecimal temp;
    temp.bits = {};
    temp.precision = 0;
    temp.sign = false;
    BigDecimal result = temp;
    //std::cout << divisor.toString() << std::endl;
    int point = 0;

    //std::cout << ": " << divided.toString() << " !!! " << divisor.toString() << std::endl;
    for (size_t i = 0; i < divisor.bits.size() + divided.bits.size(); i++) {
        //std::cout << i << ": " << temp.toString() << " ~ " << result.toString() << std::endl;
        if (i < divided.bits.size()) {
            temp.bits.push_back(divided.bits[i]);
        } else {
            temp.bits.push_back(false);
            point++;
        }
        BigDecimal x = temp;
        x.normalize();
        if (x < divisor) {
            result.bits.push_back(false);
        } else {
            temp = temp - divisor;
            result.bits.push_back(true);
        }
    }
    result.sign = (sign != other.sign);

    result.precision = precision + other.bits.size();
    //std::cout << result.precision << " " << result.bits.size() << " " << precision << " " <<  other.precision << " " << (*this).bits.size() << " " <<  other.bits.size() << std::endl;
    result.normalize();
    return result;
}