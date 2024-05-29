#include "model_credit.h"

namespace MyCalculator {

void Credit::CalculateCredit(double credit_sum, double credit_time,
                             double percent, int type_payment,
                             PaymentOutput &output) {
  percent /= 100.0;
  output.total_payment = 0.0;

  if (type_payment == 1) {
    CalculateDifferentiated(credit_sum, credit_time, percent, output);
  } else {
    CalculateAnnuity(credit_sum, credit_time, percent, output);
  }

  output.overpayment = output.total_payment - credit_sum;
}

void Credit::CalculateDifferentiated(double credit_sum, double credit_time,
                                     double percent, PaymentOutput &output) {
  const int days_in_year = 365;
  const std::vector<int> days_in_month = {31, 28, 31, 30, 31, 30,
                                          31, 31, 30, 31, 30, 31};
  double monthly_payment = credit_sum / credit_time;
  double current_sum = credit_sum;
  double first_month_interest =
      CalculateMonthlyInterest(credit_sum, percent, days_in_month[0]);
  output.first_payment = monthly_payment + first_month_interest;

  for (size_t i = 0; i < days_in_month.size(); ++i) {
    if (current_sum <= 0) break;
    double monthly_interest =
        CalculateMonthlyInterest(current_sum, percent, days_in_month[i]);
    current_sum -= monthly_payment;
    output.total_payment += monthly_payment + monthly_interest;
    if (i == days_in_month.size() - 1) {
      output.last_payment = monthly_payment + monthly_interest;
    }
  }
}

void Credit::CalculateAnnuity(double credit_sum, double credit_time,
                              double percent, PaymentOutput &output) {
  percent /= 12;
  double annuity_factor = percent / (1 - std::pow(1 + percent, -credit_time));
  output.first_payment = output.last_payment = credit_sum * annuity_factor;
  output.total_payment = output.first_payment * credit_time;
}

double Credit::CalculateMonthlyInterest(double credit_sum, double percent,
                                        int days) {
  return credit_sum * percent * days / 365;
}

}  // namespace MyCalculator
