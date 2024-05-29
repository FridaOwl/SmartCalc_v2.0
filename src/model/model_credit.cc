#include "model_credit.h"

namespace MyCalculator {

void Credit::CalculateCredit(double credit_sum, double credit_time,
                             double percent, int type_payment,
                             PaymentOutput &output) {
  percent /= 100.0;
  if (type_payment) {
    calculateDifferentiated(credit_sum, credit_time, percent, output);
  } else {
    calculateAnnuity(credit_sum, credit_time, percent, output);
  }
}

void Credit::calculateDifferentiated(double credit_sum, double credit_time,
                                     double percent, PaymentOutput &output) {
  static const int days_in_month[] = {31, 28, 31, 30, 31, 30,
                                      31, 31, 30, 31, 30, 31};
  double monthly_payment = credit_sum / credit_time;
  double current_sum = credit_sum;
  int month = 0;

  output.total_payment = 0.0;
  output.first_payment =
      monthly_payment + current_sum * percent * days_in_month[0] / 365.0;

  while (current_sum > 0) {
    double interest_payment =
        current_sum * percent * days_in_month[month] / 365.0;
    current_sum -= monthly_payment;
    output.total_payment += monthly_payment + interest_payment;
    month = (month + 1) % 12;
  }

  output.last_payment = monthly_payment + current_sum * percent *
                                              days_in_month[(month - 1) % 12] /
                                              365.0;
  output.overpayment = output.total_payment - credit_sum;
}

void Credit::calculateAnnuity(double credit_sum, double credit_time,
                              double percent, PaymentOutput &output) {
  percent /= 12.0;
  output.first_payment =
      credit_sum * percent / (1 - std::pow(1 + percent, -credit_time));
  output.total_payment = output.first_payment * credit_time;
  output.last_payment = output.first_payment;
  output.overpayment = output.total_payment - credit_sum;
}

}  // namespace MyCalculator