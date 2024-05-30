#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "model_calculator.h"
#include "model_credit.h"
#include "model_deposit.h"

namespace MyCalculator {

class CalcController {
 public:
  CalcController() = default;

  double CalculateExpression(const std::string &expression);
  void CalculateCredit(double credit_sum, double credit_time, double percent,
                       int type_payment, Credit::PaymentOutput &output);
  void CalculateDeposit(double summ, double n, double interest_rate,
                        double tax_rate, int periodicity_payments,
                        int capitalization, int count_add, double add,
                        int count_sub, double sub,
                        Deposit::DepositOutput &output);

 private:
  ModelCalculator model_;
  Credit credit_;
  Deposit deposit_;
};

}  // namespace MyCalculator

#endif  // CONTROLLER_H_
