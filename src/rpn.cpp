#include "rpn.h"
#include <stdexcept>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>

// Вспомогательная функция для разбиения строки на токены
std::vector<std::string> tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

// Вспомогательная функция для проверки, является ли строка числом
bool is_number(const std::string& s) {
    if (s.empty()) return false;

    size_t start = 0;
    // Проверяем знак числа
    if (s[0] == '-' || s[0] == '+') {
        if (s.size() == 1) return false; // Только знак без цифр
        start = 1;
    }

    bool has_dot = false;
    for (size_t i = start; i < s.size(); ++i) {
        if (s[i] == '.') {
            if (has_dot) return false; // Две точки в числе
            has_dot = true;
        } else if (!std::isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

double evaluate_rpn(const std::string& expression) {
    std::stack<double> stack;
    std::vector<std::string> tokens = tokenize(expression);

    for (const auto& token : tokens) {
        if (is_number(token)) {
            // Преобразуем строку в число и помещаем в стек
            stack.push(std::stod(token));
        } else {
            // Обрабатываем оператор
            if (stack.size() < 2) {
                throw std::invalid_argument("Not enough operands for operator '" + token + "'");
            }

            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            double result;

            if (token == "+") {
                result = a + b;
            } else if (token == "-") {
                result = a - b;
            } else if (token == "*") {
                result = a * b;
            } else if (token == "/") {
                if (b == 0.0) {
                    throw std::invalid_argument("Division by zero");
                }
                result = a / b;
            } else if (token == "^") {
                result = std::pow(a, b);
            } else {
                throw std::invalid_argument("Invalid operator: '" + token + "'");
            }

            stack.push(result);
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid expression: too many operands");
    }

    return stack.top();
}
