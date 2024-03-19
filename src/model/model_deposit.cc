#include "model_deposit.h"

namespace MyCalculator {

void MyCalculator::Deposit::CalculateDeposit(
    double summ, double n, double interest_rate, double tax_rate,
    int periodicity_payments, int capitalization, int count_add, double add,
    int count_sub, double sub, DepositOutput &output) {
  int flag = 0;
  double tax = tax_rate / 100;
  output.accrued_interest = 0;

  if (capitalization == 2) {
    for (int i = 0; i < n && !flag; i++) {
      if (count_add && count_sub)
        summ = summ + add - sub;
      else if (!count_add && count_sub)
        summ = summ - sub;
      else if (count_add && !count_sub)
        summ = summ + add;

      if (summ < 0) flag = 1;
      double month_per = (summ * interest_rate / 36500) * 30;
      output.accrued_interest += month_per;
    }
    output.result = summ + output.accrued_interest;
    if (output.accrued_interest >= 75000)
      output.tax_with = output.accrued_interest * tax;
    else
      output.tax_with = 0;
  } else if (capitalization == 1 && periodicity_payments == 2) {
    double month_per = 0;
    for (int i = 0; i < n && !flag; i++) {
      if (count_add && count_sub)
        summ = summ + add - sub + month_per;
      else if (!count_add && count_sub)
        summ = summ - sub + month_per;
      else if (count_add && !count_sub)
        summ = summ + add + month_per;
      else
        summ = summ + month_per;

      if (summ < 0) flag = 1;
      month_per = (summ * interest_rate / 36500) * 30;
      output.accrued_interest += month_per;
    }
    output.result = summ + month_per;
    if (output.accrued_interest >= 75000)
      output.tax_with = output.accrued_interest * tax;
    else
      output.tax_with = 0;
  } else if (capitalization == 1 && periodicity_payments == 1) {
    double month_per = 0;
    for (int i = 0; i < n && !flag; i++) {
      if (count_add && count_sub)
        summ = summ + add - sub;
      else if (!count_add && count_sub)
        summ = summ - sub;
      else if (count_add && !count_sub)
        summ = summ + add;

      if (summ < 0) flag = 1;
      month_per = (summ * interest_rate / 36500) * 30;
      output.accrued_interest += month_per;
    }
    output.result = summ + output.accrued_interest;
    if (output.accrued_interest >= 75000)
      output.tax_with = output.accrued_interest * tax;
    else
      output.tax_with = 0;
  }
}

}  // namespace MyCalculator