#include "controller.h"

namespace MyCalculator {

double CalcController::CalculateExpression(const std::string &expression) {
  return model_.evaluateExpression(expression);
}

void CalcController::CalculateCredit(double credit_sum, double credit_time,
                                     double percent, int type_payment,
                                     Credit::PaymentOutput &output) {
  credit_.CalculateCredit(credit_sum, credit_time, percent, type_payment,
                          output);
}

void CalcController::CalculateDeposit(double summ, double n,
                                      double interest_rate, double tax_rate,
                                      int periodicity_payments,
                                      int capitalization, int count_add,
                                      double add, int count_sub, double sub,
                                      Deposit::DepositOutput &output) {
  deposit_.CalculateDeposit(summ, n, interest_rate, tax_rate,
                            periodicity_payments, capitalization, count_add,
                            add, count_sub, sub, output);
}

}  // namespace MyCalculator
