#include "model_calculator.h"

namespace MyCalculator {

double MyCalculator::ModelCalculator::evaluateExpression(
    const std::string &expression) {
  setlocale(LC_NUMERIC, "C");
  std::string postfix = PolishNotation::toPostfix(expression);
  std::stack<double> operands;

  std::istringstream inputStream(postfix);
  std::string token;
  while (inputStream >> token) {
    if (token[0] == '+' || token[0] == '-' || token[0] == '*' ||
        token[0] == '/' || token[0] == '^' || token[0] == '%') {
      if (operands.size() < 2) {
        throw std::runtime_error("Insufficient operands for operation");
      }

      double operand2 = operands.top();
      operands.pop();
      double operand1 = operands.top();
      operands.pop();
      operands.push(binaryCalculate(token[0], operand1, operand2));
    }

    else if (isalpha(token[0])) {
      if (operands.empty()) {
        throw std::runtime_error("Expected argument for unary function");
      }
      double operand1 = operands.top();
      operands.pop();
      operands.push(unaryCalculate(token[0], operand1));
    } else {
      operands.push(std::stod(token));
    }
  }
  if (operands.size() != 1) {
    throw std::runtime_error("Error in expression");
  }

  return operands.top();
}

double MyCalculator::ModelCalculator::unaryCalculate(char func,
                                                     double operand) {
  switch (func) {
    case 's':
      return sin(operand);
    case 'c':
      return cos(operand);
    case 't':
      return tan(operand);
    case 'i':
      return asin(operand);
    case 'o':
      return acos(operand);
    case 'n':
      return atan(operand);
    case 'q':
      if (operand < 0.0) {
        throw std::runtime_error("Negative value under the square root");
      }
      return sqrt(operand);
    case 'l':
      if (operand <= 0.0) {
        throw std::runtime_error("Natural logarithm of a non-positive number");
      }
      return log(operand);
    case 'g':
      if (operand <= 0.0) {
        throw std::runtime_error("Logarithm of a non-positive number");
      }
      return log10(operand);
    case 'u':
      return 0 - operand;
    default:
      throw std::runtime_error("Unknown unary function");
  }
}

double MyCalculator::ModelCalculator::binaryCalculate(char operation,
                                                      double operand1,
                                                      double operand2) {
  switch (operation) {
    case '+':
      return operand1 + operand2;
    case '-':
      return operand1 - operand2;
    case '*':
      return operand1 * operand2;
    case '/':
      if (operand2 == 0.0) {
        throw std::runtime_error("Division by zero");
      }
      return operand1 / operand2;
    case '%':
      return fmod(operand1, operand2);
    case '^':
      return pow(operand1, operand2);
    default:
      throw std::runtime_error("Unknown binary operation");
  }
}

}  // namespace MyCalculator