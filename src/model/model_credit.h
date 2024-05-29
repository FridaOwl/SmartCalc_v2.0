#ifndef MODEL_CREDIT_H_
#define MODEL_CREDIT_H_

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

namespace MyCalculator {

class Credit {
 public:
  struct PaymentOutput {
    double total_payment;
    double first_payment;
    double last_payment;
    double overpayment;
  };

  Credit() {}
  void CalculateCredit(double credit_sum, double credit_time, double percent,
                       int type_payment, PaymentOutput &output);

 private:
  void CalculateDifferentiated(double credit_sum, double credit_time,
                               double percent, PaymentOutput &output);
  void CalculateAnnuity(double credit_sum, double credit_time, double percent,
                        PaymentOutput &output);
  double CalculateMonthlyInterest(double credit_sum, double percent, int days);
};

}  // namespace MyCalculator

#endif  // MODEL_CREDIT_H_
