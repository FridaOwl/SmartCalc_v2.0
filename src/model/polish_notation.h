#ifndef POLISH_NOTATION_H_
#define POLISH_NOTATION_H_

#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>

namespace MyCalculator {

class PolishNotation {
 public:
  /**
   * Converts an infix expression to postfix.
   *
   * @param infix input string in infix notation.
   * @return string in postfix notation.
   * @throws std::invalid_argument if the input expression is invalid.
   */
  static std::string toPostfix(const std::string &infix);

  /**
   * Processes numeric values, including decimal and scientific notation,
   * adding them to the postfix string.
   *
   * @param infix The infix expression to process.
   * @param index The index of the current character in the infix expression.
   * @param postfix The string to which the postfix expression is added.
   */
  static void findNumeric(const std::string &infix, size_t &index,
                          std::string &postfix);

  /**
   * Checks if a character is an operation symbol.
   *
   * @param c The character to check.
   * @return true if the character is an operation symbol, false otherwise.
   */
  static bool operation(char c);

  /**
   * Determines the priority of an operation.
   *
   * @param c The operation symbol.
   * @return The priority of the operation.
   */
  static int priorityOperation(char c);

 private:
  static const std::map<std::string, char> functions;
};

}  // namespace MyCalculator

#endif  // POLISH_NOTATION_H_
