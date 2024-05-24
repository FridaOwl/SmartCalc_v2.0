#include "model_calculator.h"

namespace MyCalculator {

double MyCalculator::ModelCalculator::evaluateExpression(const std::string &expression) {
    setlocale(LC_NUMERIC, "C");
    std::string postfix = PolishNotation::toPostfix(expression);
    std::stack<double> operands;
    std::istringstream inputStream(postfix);
    std::string token;

    while (inputStream >> token) {
        if (isOperator(token[0])) {
            processOperator(token[0], operands);
        } else if (isFunction(token[0])) {
            processFunction(token[0], operands);
        } else {
            operands.push(std::stod(token));
        }
    }

    if (operands.size() != 1) {
        throw std::runtime_error("Error in expression");
    }

    return operands.top();
}

bool MyCalculator::ModelCalculator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
}

bool MyCalculator::ModelCalculator::isFunction(char c) {
    return isalpha(c);
}

void MyCalculator::ModelCalculator::processOperator(char op, std::stack<double> &operands) {
    if (operands.size() < 2) {
        throw std::runtime_error("Insufficient operands for operation");
    }
    double operand2 = operands.top(); operands.pop();
    double operand1 = operands.top(); operands.pop();
    operands.push(binaryCalculate(op, operand1, operand2));
}

void MyCalculator::ModelCalculator::processFunction(char func, std::stack<double> &operands) {
    if (operands.empty()) {
        throw std::runtime_error("Expected argument for unary function");
    }
    double operand = operands.top(); operands.pop();
    operands.push(unaryCalculate(func, operand));
}

double MyCalculator::ModelCalculator::unaryCalculate(char func, double operand) {
    switch (func) {
        case 's': return sin(operand);
        case 'c': return cos(operand);
        case 't': return tan(operand);
        case 'i': return asin(operand);
        case 'o': return acos(operand);
        case 'n': return atan(operand);
        case 'q': return sqrtCheck(operand);
        case 'l': return logCheck(operand);
        case 'g': return log10Check(operand);
        case 'u': return -operand;
        default: throw std::runtime_error("Unknown unary function");
    }
}

double MyCalculator::ModelCalculator::sqrtCheck(double operand) {
    if (operand < 0.0) {
        throw std::runtime_error("Negative value under the square root");
    }
    return sqrt(operand);
}

double MyCalculator::ModelCalculator::logCheck(double operand) {
    if (operand <= 0.0) {
        throw std::runtime_error("Natural logarithm of a non-positive number");
    }
    return log(operand);
}

double MyCalculator::ModelCalculator::log10Check(double operand) {
    if (operand <= 0.0) {
        throw std::runtime_error("Logarithm of a non-positive number");
    }
    return log10(operand);
}

double MyCalculator::ModelCalculator::binaryCalculate(char operation, double operand1, double operand2) {
    switch (operation) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return divisionCheck(operand1, operand2);
        case '%': return fmod(operand1, operand2);
        case '^': return pow(operand1, operand2);
        default: throw std::runtime_error("Unknown binary operation");
    }
}

double MyCalculator::ModelCalculator::divisionCheck(double operand1, double operand2) {
    if (operand2 == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    return operand1 / operand2;
}

}  // namespace MyCalculator
