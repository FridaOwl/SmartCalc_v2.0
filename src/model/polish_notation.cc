#include "polish_notation.h"

#include "string_validation.h"

namespace MyCalculator {

const std::map<std::string, char> PolishNotation::functions = {
    {"sin", 's'},  {"cos", 'c'},  {"tan", 't'}, {"asin", 'i'}, {"acos", 'o'},
    {"atan", 'n'}, {"sqrt", 'q'}, {"ln", 'l'},  {"log", 'g'}};

std::string PolishNotation::toPostfix(const std::string &infix) {
  std::stack<char> operatorStack;
  std::string postfix = "";
  std::map<char, int> priority = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2},
                                  {'%', 2}, {'u', 4}, {'^', 5}};

  StringValidator checkString(infix);
  if (!checkString.IsValid()) {
    throw std::invalid_argument("Invalid equation!");
  }

  for (size_t i = 0; i < infix.size(); i++) {
    char c = infix[i];
    if (std::isdigit(c) || c == '.') {
      findNumeric(infix, i, postfix);
    } else if (c == '(') {
      operatorStack.push(c);
    } else if (c == ')') {
      while (!operatorStack.empty() && operatorStack.top() != '(') {
        postfix += operatorStack.top();
        postfix += ' ';
        operatorStack.pop();
      }
      if (!operatorStack.empty()) {
        operatorStack.pop();
      }
    } else if (c == '-') {
      if (i == 0 || infix[i - 1] == '(' || isOperation(infix[i - 1])) {
        operatorStack.push('u');
      } else {
        while (!operatorStack.empty() && operatorStack.top() != '(' &&
               operationPriority(operatorStack.top()) >= operationPriority(c)) {
          postfix += operatorStack.top();
          postfix += ' ';
          operatorStack.pop();
        }
        operatorStack.push(c);
      }
    } else if (isOperation(c)) {
      while (!operatorStack.empty() && operatorStack.top() != '(' &&
             (c != '^' ? operationPriority(operatorStack.top()) >=
                             operationPriority(c)
                       : operationPriority(operatorStack.top()) >
                             operationPriority(c))) {
        postfix += operatorStack.top();
        postfix += ' ';
        operatorStack.pop();
      }
      operatorStack.push(c);
    } else {
      std::string fx = "";
      while (i < infix.size() && std::isalpha(infix[i])) {
        fx += infix[i++];
      }
      --i;
      if (functions.find(fx) != functions.end()) {
        operatorStack.push(functions.at(fx));
      }
    }
  }

  while (!operatorStack.empty()) {
    postfix += operatorStack.top();
    postfix += ' ';
    operatorStack.pop();
  }

  return postfix;
}

void PolishNotation::findNumeric(const std::string &infix, size_t &index,
                                 std::string &postfix) {
  while (index < infix.size() &&
         (std::isdigit(infix[index]) || infix[index] == '.' ||
          infix[index] == 'e' || infix[index] == 'E')) {
    postfix += infix[index];
    if ((infix[index] == 'e' || infix[index] == 'E') &&
        index + 1 < infix.size() &&
        (infix[index + 1] == '+' || infix[index + 1] == '-')) {
      postfix += infix[++index];
      if (index + 1 < infix.size() && std::isdigit(infix[index + 1])) {
        postfix += infix[++index];
      } else {
        throw std::invalid_argument("Invalid scientific notation");
      }
    }
    index++;
  }
  postfix += ' ';
  index--;
}

bool PolishNotation::isOperation(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' ||
         c == 'u';
}

int PolishNotation::operationPriority(char c) {
  switch (c) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
    case '%':
      return 2;
    case 'u':
      return 4;
    case '^':
      return 5;
    default:
      return 6;
  }
}

}  // namespace MyCalculator
