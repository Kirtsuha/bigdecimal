#include "bigdecimal.h"
#include <iostream>
#include <chrono>

// Функция для вычисления числа Пи с заданной точностью
BigDecimal calculatePi(int precision) {
    // Инициализация переменных
    BigDecimal pi("0", precision); // Результат (число Пи)
    BigDecimal term("1", precision); // Текущий член ряда
    bool subtract = false; // Флаг для чередования знаков

    // Вычисление ряда Лейбница
    for (int i = 1; term != BigDecimal("0", precision); i += 2) {
        if (subtract) {
            pi = pi - (BigDecimal("4", precision) / BigDecimal(std::to_string(i), precision));
        } else {
            pi = pi + (BigDecimal("4", precision) / BigDecimal(std::to_string(i), precision));
        }
        subtract = !subtract;
    }

    return pi;
}

int main(int argc, char* argv[]) {
    int precision = std::atoi(argv[1]);

    // Запуск таймера
    auto start = std::chrono::high_resolution_clock::now();

    // Вычисление числа Пи
    BigDecimal pi = calculatePi(precision);

    // Остановка таймера
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Вывод результата
    std::cout << "Pi: " << pi.toString() << std::endl;
    std::cout << "Calculation time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}