#include "bigdecimal.h"
#include <iostream>
#include <chrono>
#include <cmath>

// Функция для вычисления числа Пи с заданной точностью
BigDecimal calculate_pi(int precision) {
    precision = static_cast<int>(std::ceil(precision* std::log2(10)));
    BigDecimal pi("3.0");
    BigDecimal epsilon = BigDecimal("0.1");
    for (int i = 0; i < precision; ++i) {
        epsilon = epsilon * BigDecimal("0.1"); // epsilon = 10^{-precision}
    }
    //std::cout << epsilon.toString();

    BigDecimal sign("1.0");
    BigDecimal denominator("2.0"); // Начинаем с 2*3*4
    int step = 0;
    BigDecimal term;

    do {
        term = BigDecimal("4.0") / (denominator * (denominator + BigDecimal("1.0")) * (denominator + BigDecimal("2.0")));
        std::cout << term.toString() << std::endl;
        term = term * sign;

        pi = pi + term;

        sign = sign * BigDecimal("-1.0");
        
        denominator = denominator + BigDecimal("2.0");
        step++;
    } while (term > epsilon || term < epsilon * BigDecimal("-1.0"));
    //std::cout << step;
    return pi;
}

int main(int argc, char* argv[]) {
    int precision = std::atoi(argv[1]);

    // Запуск таймера
    auto start = std::chrono::high_resolution_clock::now();

    // Вычисление числа Пи
    BigDecimal pi = calculate_pi(precision);

    // Остановка таймера
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Вывод результата
    //std::cout << BigDecimal("1.23").toDouble() << " " << BigDecimal("1.23").toString() << std::endl;
    std::cout << "Pi: " << pi.toDouble() << std::endl;
    std::cout << "Calculation time: " << elapsed.count() << " seconds" << std::endl;
    return 0;
}