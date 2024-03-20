#include <gtest/gtest.h>

#include "../model/model_calculator.h"
#include "../model/model_credit.h"
#include "../model/model_deposit.h"
#include "../model/polish_notation.h"
#include "../model/string_validation.h"

TEST(StringValidatorTest, ValidString1) {
  MyCalculator::StringValidator validator("1+2*3-sin(90)/tan(45+2*3)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString2) {
  MyCalculator::StringValidator validator("ln(2+2)*log(10)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString3) {
  MyCalculator::StringValidator validator("sqrt(16*16+9*9)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString4) {
  MyCalculator::StringValidator validator("1+(2*(3+4)-5)/6");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString5) {
  MyCalculator::StringValidator validator("asin(0.5)^2");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString6) {
  MyCalculator::StringValidator validator("cos(90)*tan(45)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString8) {
  MyCalculator::StringValidator validator("sqrt(2+2*2)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString9) {
  MyCalculator::StringValidator validator("(2+2)*(3+3)/(4+4)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString11) {
  MyCalculator::StringValidator validator("2^3^2");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString12) {
  MyCalculator::StringValidator validator("log(100/10)*ln(7+7)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString13) {
  MyCalculator::StringValidator validator("1/(1+1)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString14) {
  MyCalculator::StringValidator validator("sin(30+30)+cos(60)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString15) {
  MyCalculator::StringValidator validator("sqrt(2)*sqrt(2)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString16) {
  MyCalculator::StringValidator validator("acos(0.5)^atan(1)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString17) {
  MyCalculator::StringValidator validator("-5+5*(-6)");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString1) {
  MyCalculator::StringValidator validator("1+2++3");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString2) {
  MyCalculator::StringValidator validator("sin(90(90))");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString3) {
  MyCalculator::StringValidator validator("1()2");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString4) {
  MyCalculator::StringValidator validator("(1+2");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString5) {
  MyCalculator::StringValidator validator("tan(45)+");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString6) {
  MyCalculator::StringValidator validator("cos90)*tan(45)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString7) {
  MyCalculator::StringValidator validator("ln(2.71");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString8) {
  MyCalculator::StringValidator validator("sqrt+2+2*2)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString9) {
  MyCalculator::StringValidator validator("(2+2(3+3)/(4+4)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString10) {
  MyCalculator::StringValidator validator("2^3^");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString11) {
  MyCalculator::StringValidator validator("log(100/10)*ln(7+7+)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString12) {
  MyCalculator::StringValidator validator("sin30+30)+cos(60)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString13) {
  MyCalculator::StringValidator validator("sqrt(2*sqrt(2)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString14) {
  MyCalculator::StringValidator validator("1..2+2");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString15) {
  MyCalculator::StringValidator validator("()");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, InvalidString16) {
  MyCalculator::StringValidator validator("sin5");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, UnknownFunction) {
  MyCalculator::StringValidator validator("blah(30)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, ClosingParenthesisBeforeNumber) {
  MyCalculator::StringValidator validator("1+2)3");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, ClosingParenthesisAfterOperator) {
  MyCalculator::StringValidator validator("1+*2)");
  ASSERT_FALSE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString18) {
  MyCalculator::StringValidator validator("1.340781e+154");
  ASSERT_TRUE(validator.IsValid());
}

TEST(StringValidatorTest, ValidString33) {
  MyCalculator::StringValidator validator("1.1.1+3");
  ASSERT_FALSE(validator.IsValid());
}

TEST(CalcTest, Test1) {
  MyCalculator::ModelCalculator test("2+5*3");
  EXPECT_NEAR(test.evaluateExpression("2+5*3"), 17, 1e-6);
}

TEST(CalcTest, Test2) {
  MyCalculator::ModelCalculator test("(3^3+4^2)*2");
  EXPECT_NEAR(test.evaluateExpression("(3^3+4^2)*2"), 86, 1e-6);
}

TEST(CalcTest, Test3) {
  MyCalculator::ModelCalculator test(
      "2+3*4-5^6/tan(30)+7*8/9-10+asin(1)-acos(0)+atan(1)");
  EXPECT_NEAR(test.evaluateExpression(
                  "2+3*4-5^6/tan(30)+7*8/9-10+asin(1)-acos(0)+atan(1)"),
              2450.38, 1e-2);
}

TEST(CalcTest, Test4) {
  MyCalculator::ModelCalculator test("sqrt(4)+log(5)");
  EXPECT_NEAR(test.evaluateExpression("sqrt(4)+log(5)"), 2.698970, 1e-6);
}

TEST(CalcTest, Test5) {
  MyCalculator::ModelCalculator test;
  EXPECT_THROW(test.evaluateExpression("5/0"), std::runtime_error);
}

TEST(ModelCalculatorTest, UnaryMinusComplexTest) {
  MyCalculator::ModelCalculator calc("-4+(-4)*(-2)-sin(-30)");
  EXPECT_NEAR(calc.evaluateExpression("-4+(-4)*(-2)-sin(-30)"), 3.01197, 1e-5);
}

TEST(ModelCalculatorTest, CosFunction) {
  MyCalculator::ModelCalculator calc("cos(90)");
  EXPECT_NEAR(calc.evaluateExpression("cos(90)"), -0.44807, 1e-5);
}

TEST(CalcTest, Test6) {
  MyCalculator::ModelCalculator test;
  EXPECT_THROW(test.evaluateExpression("log(-5)"), std::runtime_error);
}

TEST(CalcTest, Test7) {
  MyCalculator::ModelCalculator test;
  EXPECT_THROW(test.evaluateExpression("ln(-5)"), std::runtime_error);
}

TEST(CalcTest, Test8) {
  MyCalculator::ModelCalculator test;
  EXPECT_THROW(test.evaluateExpression("sqrt(-5)"), std::runtime_error);
}

TEST(ModelCalculatorTest, Test9) {
  MyCalculator::ModelCalculator calc("10%3");
  EXPECT_NEAR(calc.evaluateExpression("10%3"), 1, 1e-5);
}

TEST(CalcTest, Test10) {
  MyCalculator::ModelCalculator test("ln(10)+log(5)");
  EXPECT_NEAR(test.evaluateExpression("ln(10)+log(5)"), 3.001555, 1e-6);
}

TEST(CalcTest, Test11) {
  MyCalculator::ModelCalculator test("-3^4");
  EXPECT_NEAR(test.evaluateExpression("-3^4"), -81, 1e-6);
}

TEST(CreditTest, DifferentialPayment) {
  MyCalculator::Credit credit;
  double credit_sum = 120000;
  double credit_time = 12;
  double percent = 10;
  int type_payment = 1;
  MyCalculator::Credit::PaymentOutput output;

  credit.CalculateCredit(credit_sum, credit_time, percent, type_payment,
                         output);

  ASSERT_NEAR(output.total_payment, 126473.97, 1e-2);
  ASSERT_NEAR(output.first_payment, 11019.18, 1e-2);
  ASSERT_NEAR(output.last_payment, 10084.93, 1e-2);
  ASSERT_NEAR(output.overpayment, 6473.97, 1e-2);
}

TEST(CreditTest, AnnuityPayment) {
  MyCalculator::Credit credit;
  double credit_sum = 120000;
  double credit_time = 12;
  double percent = 10;
  int type_payment = 0;
  MyCalculator::Credit::PaymentOutput output;

  credit.CalculateCredit(credit_sum, credit_time, percent, type_payment,
                         output);

  ASSERT_NEAR(output.total_payment, 126598.88, 1e-2);
  ASSERT_NEAR(output.first_payment, 10549.91, 1e-2);
  ASSERT_NEAR(output.last_payment, 10549.91, 1e-2);
  ASSERT_NEAR(output.overpayment, 6598.88, 1e-2);
}

TEST(DepositTest, TestWithoutOperations) {
  MyCalculator::Deposit deposit;

  double sum = 10000;
  double credit_time = 12;
  double interest_rate = 11;
  double tax_rate = 1;
  int periodicity_payments = 2;
  int capitalization = 2;
  int count_add = 2;
  double add = 0;
  int count_sub = 2;
  double sub = 0;
  MyCalculator::Deposit::DepositOutput output;

  deposit.CalculateDeposit(sum, credit_time, interest_rate, tax_rate,
                           periodicity_payments, capitalization, count_add, add,
                           count_sub, sub, output);

  ASSERT_NEAR(output.accrued_interest, 1084.93, 1e-2);
  ASSERT_NEAR(output.result, 11084.93, 1e-2);
  ASSERT_NEAR(output.tax_with, 0.00, 1e-2);
}

TEST(DepositTest, TestWithCapitalisation) {
  MyCalculator::Deposit deposit;

  double sum = 10000;
  double credit_time = 12;
  double interest_rate = 11;
  double tax_rate = 1;
  int periodicity_payments = 2;
  int capitalization = 1;
  int count_add = 2;
  double add = 0;
  int count_sub = 2;
  double sub = 0;
  MyCalculator::Deposit::DepositOutput output;

  deposit.CalculateDeposit(sum, credit_time, interest_rate, tax_rate,
                           periodicity_payments, capitalization, count_add, add,
                           count_sub, sub, output);

  ASSERT_NEAR(output.accrued_interest, 1140.54, 1e-2);
  ASSERT_NEAR(output.result, 11140.54, 1e-2);
  ASSERT_NEAR(output.tax_with, 0.00, 1e-2);
}

TEST(DepositTest, TestWithAddOnceMonth) {
  MyCalculator::Deposit deposit;

  double sum = 10000;
  double credit_time = 12;
  double interest_rate = 11;
  double tax_rate = 1;
  int periodicity_payments = 2;
  int capitalization = 2;
  int count_add = 1;
  double add = 1000;
  int count_sub = 2;
  double sub = 0;
  MyCalculator::Deposit::DepositOutput output;

  deposit.CalculateDeposit(sum, credit_time, interest_rate, tax_rate,
                           periodicity_payments, capitalization, count_add, add,
                           count_sub, sub, output);

  ASSERT_NEAR(output.accrued_interest, 1790.14, 1e-2);
  ASSERT_NEAR(output.result, 23790.14, 1e-2);
  ASSERT_NEAR(output.tax_with, 0.00, 1e-2);
}

TEST(DepositTest, TestWithSubOnceMonth) {
  MyCalculator::Deposit deposit;

  double sum = 10000;
  double credit_time = 12;
  double interest_rate = 11;
  double tax_rate = 1;
  int periodicity_payments = 2;
  int capitalization = 2;
  int count_add = 2;
  double add = 0;
  int count_sub = 1;
  double sub = 100;
  MyCalculator::Deposit::DepositOutput output;

  deposit.CalculateDeposit(sum, credit_time, interest_rate, tax_rate,
                           periodicity_payments, capitalization, count_add, add,
                           count_sub, sub, output);

  ASSERT_NEAR(output.accrued_interest, 1014.41, 1e-2);
  ASSERT_NEAR(output.result, 9814.41, 1e-2);
  ASSERT_NEAR(output.tax_with, 0.00, 1e-2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}