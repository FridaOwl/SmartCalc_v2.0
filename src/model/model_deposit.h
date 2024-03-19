#ifndef MODEL_DEPOSIT_H_
#define MODEL_DEPOSIT_H_

#include <cmath>
#include <iostream>

namespace MyCalculator {

class Deposit {
 public:
  struct DepositOutput {
    double result;
    double tax_with;
    double accrued_interest;
  };

  Deposit() {}
  void CalculateDeposit(double summ, double n, double interest_rate,
                        double tax_rate, int periodicity_payments,
                        int capitalization, int count_add, double add,
                        int count_sub, double sub, DepositOutput &output);
};

}  // namespace MyCalculator

#endif  // MODEL_DEPOSIT_H_