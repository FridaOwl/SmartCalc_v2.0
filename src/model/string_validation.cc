#include "string_validation.h"

namespace MyCalculator {

bool StringValidator::IsValid() const {
  bool valid = true;
  for (size_t i = 0; i < stringEquation_.length() && valid; ++i) {
    char currentSymbol = stringEquation_[i];
    if (IsDigitOrDot(currentSymbol)) {
      valid = IsValidNumber(stringEquation_, i);
    } else if (IsOperator(currentSymbol)) {
      valid = IsValidOperator(i);
    } else if (IsOpeningBracket(currentSymbol)) {
      valid = HandleOpenBracket(i);
    } else if (IsClosingBracket(currentSymbol)) {
      valid = HandleCloseBracket(i);
    } else {
      valid = IsValidFunction(i);
    }
  }
  if (IsOperator(stringEquation_.back()) || open_bracket != close_bracket) {
    valid = false;
  }
  return valid;
}

bool StringValidator::IsValidNumber(const std::string &str, size_t &pos) const {
  bool hasDot = false;
  bool hasExp = false;
  bool digitBefore = false;

  while (pos < str.length() && IsDigitOrDot(str[pos])) {
    char ch = str[pos];

    if (std::isdigit(ch)) {
      digitBefore = true;
    } else if (ch == '.') {
      if (hasDot || hasExp) return false;
      hasDot = true;
    } else if (ch == 'e' || ch == 'E') {
      if (!digitBefore || hasExp) return false;
      hasExp = true;
      digitBefore = false;

      if (++pos < str.length() && (str[pos] == '+' || str[pos] == '-')) {
        if (++pos >= str.length() || !std::isdigit(str[pos])) return false;
        digitBefore = true;
      } else if (!std::isdigit(str[pos])) {
        return false;
      } else {
        digitBefore = true;
      }
    }
    pos++;
  }

  return hasExp ? digitBefore : true;
}

bool StringValidator::IsValidOperator(size_t i) const {
  if (i == 0 && stringEquation_[i] != '-') return false;
  if (stringEquation_[i] == '-' &&
      (i == 0 || IsOpeningBracket(stringEquation_[i - 1]) ||
       IsOperator(stringEquation_[i - 1]))) {
    return true;
  }
  if (i > 0 && (IsOperator(stringEquation_[i - 1]) ||
                IsOpeningBracket(stringEquation_[i - 1]) ||
                (i < stringEquation_.length() - 1 &&
                 IsClosingBracket(stringEquation_[i + 1])))) {
    return false;
  }
  return true;
}

bool StringValidator::HandleOpenBracket(size_t i) const {
  if (i > 0 && (std::isdigit(stringEquation_[i - 1]) ||
                IsClosingBracket(stringEquation_[i - 1]))) {
    return false;
  }
  if (i + 1 < stringEquation_.length() &&
      IsClosingBracket(stringEquation_[i + 1])) {
    return false;
  }
  open_bracket++;
  return true;
}

bool StringValidator::HandleCloseBracket(size_t i) const {
  if (i + 1 < stringEquation_.length() &&
      std::isdigit(stringEquation_[i + 1])) {
    return false;
  }
  close_bracket++;
  if (i == 0 || IsOperator(stringEquation_[i - 1])) {
    return false;
  }
  return true;
}

bool StringValidator::IsValidFunction(size_t &i) const {
  for (const std::string &func : functions) {
    if (stringEquation_.substr(i, func.length()) == func) {
      i += func.length() - 1;
      return i + 1 < stringEquation_.length() &&
             IsOpeningBracket(stringEquation_[i + 1]);
    }
  }
  return false;
}

bool StringValidator::IsDigitOrDot(char c) const {
  return std::isdigit(c) || c == '.' || c == 'e' || c == 'E';
}

bool StringValidator::IsOperator(char c) const {
  return operators.find(c) != std::string::npos;
}

bool StringValidator::IsFunctionChar(char c) const { return std::isalpha(c); }

bool StringValidator::IsOpeningBracket(char c) const { return c == '('; }

bool StringValidator::IsClosingBracket(char c) const { return c == ')'; }

}  // namespace MyCalculator
