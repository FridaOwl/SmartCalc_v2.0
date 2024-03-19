#ifndef STRING_VALIDATION_H_
#define STRING_VALIDATION_H_

#include <cctype>
#include <iostream>
#include <set>
#include <string>

namespace MyCalculator {

class StringValidator {
 public:
  explicit StringValidator(const std::string &input) : stringEquation_(input) {}

  /**
   * @brief Checks if the string is valid.
   *
   * @return true if the string is valid.
   * @return false if the string is invalid.
   */
  bool IsValid() const;

 private:
  const std::string operators = "+-*/^%";
  const std::set<std::string> functions = {
      "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"};
  mutable int open_bracket = 0;
  mutable int close_bracket = 0;
  bool IsValidNumber(const std::string &equation, size_t &index) const;
  bool IsValidOperator(size_t i) const;
  bool HandleOpenBracket(size_t i) const;
  bool HandleCloseBracket(size_t i) const;
  bool IsValidFunction(size_t &i) const;

  std::string stringEquation_;
};

}  // namespace MyCalculator

#endif  // STRING_VALIDATION_H_
