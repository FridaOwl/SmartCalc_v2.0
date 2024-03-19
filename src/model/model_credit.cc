#include "model_credit.h"

namespace MyCalculator {

void MyCalculator::Credit::CalculateCredit(double credit_sum,
                                           double credit_time, double percent,
                                           int type_payment,
                                           PaymentOutput &output) {
  double sd = credit_sum / credit_time;
  double sp = 1.0;
  double start_credit_sum = credit_sum;

  if (type_payment) {
    double days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i = 0;
    percent = percent / 100.0;
    output.total_payment = 0.0;
    output.first_payment = sd + credit_sum * percent * days[0] / 365.0;
    while (credit_sum > 0) {
      sp = credit_sum * percent * days[i] / 365.0;
      credit_sum = credit_sum - sd;
      output.total_payment = output.total_payment + sd + sp;
      if (i == 11) {
        i = 0;
      } else {
        i++;
      }
    }
    output.last_payment = sp + sd;
  } else {
    percent = percent / 1200;
    output.last_payment = output.first_payment =
        credit_sum * percent / (1 - std::pow((1 + percent), (0 - credit_time)));
    output.total_payment = output.first_payment * credit_time;
  }

  output.overpayment = output.total_payment - start_credit_sum;
}

}  // namespace MyCalculator