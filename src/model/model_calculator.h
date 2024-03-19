#ifndef MODEL_CALCULATOR_H_
#define MODEL_CALCULATOR_H_

#include <cmath>
#include <sstream>
#include <stack>
#include <stdexcept>

#include "polish_notation.h"

namespace MyCalculator {

class ModelCalculator {
 public:
  ModelCalculator() : answer_(0){};
  ModelCalculator(const std::string &express)
      : answer_(evaluateExpression(express)) {}
  double evaluateExpression(const std::string &expression);
  double unaryCalculate(char func, double operand);
  double binaryCalculate(char operation, double operand1, double operand2);

 private:
  double answer_;
};

}  // namespace MyCalculator

#endif  // MODEL_CALCULATOR_H_
