#ifndef POLISH_NOTATION_H_
#define POLISH_NOTATION_H_

#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>

#include "model_calculator.h"
#include "string_validation.h"

namespace MyCalculator {

class PolishNotation {
 public:
  static std::string toPostfix(const std::string &infix);
  static const std::map<std::string, char> functions;

 private:
  static void findNumeric(const std::string &infix, size_t &index,
                          std::string &postfix);
  static bool operation(char c);
  static int priorityOperation(char c);
  static void handleClosingParenthesis(std::stack<char> &operatorStack,
                                       std::string &postfix);
  static void handleOperator(char c, std::stack<char> &operatorStack,
                             std::string &postfix);
  static void handleFunction(const std::string &infix, size_t &index,
                             std::stack<char> &operatorStack);
};

}  // namespace MyCalculator

#endif  // POLISH_NOTATION_H_
