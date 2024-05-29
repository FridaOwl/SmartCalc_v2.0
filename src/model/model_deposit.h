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

 private:
  void applyAdditionsAndSubtractions(double &summ, int count_add, double add,
                                     int count_sub, double sub);
  double calculateMonthlyInterest(double summ, double interest_rate);
  double applyMonthlyInterest(double &summ, double month_per,
                              int capitalization);
  double calculateTax(double accrued_interest, double tax);
};

}  // namespace MyCalculator

#endif  // MODEL_DEPOSIT_H_