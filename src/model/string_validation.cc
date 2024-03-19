#include "string_validation.h"

namespace MyCalculator {

bool MyCalculator::StringValidator::IsValid() const {
  bool valid = true;
  for (size_t i = 0; i < stringEquation_.length() && valid; ++i) {
    char currentSymbol = stringEquation_[i];
    if (std::isdigit(currentSymbol) || currentSymbol == '.' ||
        currentSymbol == 'e' || currentSymbol == 'E') {
      if (!IsValidNumber(stringEquation_, i)) {
        valid = false;
        break;
      }
    } else if (operators.find(currentSymbol) != std::string::npos) {
      if (!IsValidOperator(i)) {
        valid = false;
      }
    } else if (currentSymbol == '(') {
      valid = HandleOpenBracket(i);
    } else if (currentSymbol == ')') {
      valid = HandleCloseBracket(i);
    } else {
      if (!IsValidFunction(i)) {
        valid = false;
        break;
      }
    }
  }
  if (operators.find(stringEquation_.back()) != std::string::npos ||
      open_bracket != close_bracket) {
    valid = false;
  }

  return valid;
};

bool MyCalculator::StringValidator::IsValidNumber(const std::string& str,
                                                  size_t& pos) const {
  bool hasDot = false;
  bool hasExp = false;
  bool digitBefore = false;

  while (pos < str.length()) {
    char ch = str[pos];

    if (std::isdigit(ch)) {
      digitBefore = true;
    } else if (ch == '.') {
      if (hasDot || hasExp) {
        return false;
      }
      hasDot = true;
    } else if (ch == 'e' || ch == 'E') {
      if (!digitBefore || hasExp) {
        return false;
      }
      hasExp = true;
      digitBefore = false;

      if (++pos < str.length()) {
        char nextChar = str[pos];
        if (nextChar == '+' || nextChar == '-') {
          if (++pos < str.length() && std::isdigit(str[pos])) {
            digitBefore = true;
          } else {
            return false;
          }
        } else if (!std::isdigit(nextChar)) {
          return false;
        } else {
          digitBefore = true;
        }
      } else {
        return false;
      }
    } else {
      pos--;
      break;
    }

    pos++;
  }

  if (hasExp && !digitBefore) {
    return false;
  }

  return true;
}

bool MyCalculator::StringValidator::IsValidOperator(size_t i) const {
  if (i == 0 && stringEquation_[i] != '-') return false;
  if (stringEquation_[i] == '-' &&
      (i == 0 || stringEquation_[i - 1] == '(' ||
       operators.find(stringEquation_[i - 1]) != std::string::npos)) {
    return true;
  }
  if (i > 0 && operators.find(stringEquation_[i - 1]) != std::string::npos)
    return false;
  if (i > 0 && stringEquation_[i - 1] == '(') return false;
  if (i < stringEquation_.length() - 1 && stringEquation_[i + 1] == ')')
    return false;
  return true;
}

bool MyCalculator::StringValidator::HandleOpenBracket(size_t i) const {
  if (i > 0 &&
      (std::isdigit(stringEquation_[i - 1]) || stringEquation_[i - 1] == ')')) {
    return false;
  }
  if (i + 1 < stringEquation_.length() && stringEquation_[i + 1] == ')') {
    return false;
  }
  open_bracket++;
  return true;
}

bool MyCalculator::StringValidator::HandleCloseBracket(size_t i) const {
  if (i + 1 < stringEquation_.length() &&
      std::isdigit(stringEquation_[i + 1])) {
    return false;
  }
  close_bracket++;
  if (i == 0 || operators.find(stringEquation_[i - 1]) != std::string::npos) {
    return false;
  }

  return true;
}

bool MyCalculator::StringValidator::IsValidFunction(size_t& i) const {
  bool found_func = false;
  for (const std::string& func : functions) {
    if (stringEquation_.substr(i, func.length()) == func) {
      found_func = true;
      i += func.length() - 1;
      if (i + 1 == stringEquation_.length() || stringEquation_[i + 1] != '(') {
        return false;
      }
      break;
    }
  }
  return found_func;
}

}  // namespace MyCalculator