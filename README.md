# MyCalculator

## Описание

**MyCalculator** - это мощный и гибкий калькулятор, который поддерживает вычисления в польской нотации, а также расчеты кредита и депозита. Проект написан на C++ и предоставляет удобный интерфейс для выполнения различных финансовых и математических операций.

## Функциональные возможности

- **Математические вычисления**: Поддержка сложных математических выражений, в том числе функций и операций.
- **Расчет кредита**: Возможность расчета аннуитетных и дифференцированных платежей.
- **Расчет депозита**: Поддержка расчетов с различными периодичностями выплат и капитализацией процентов.

## Установка

### Требования

- Компилятор C++ с поддержкой C++11 или новее.
- CMake для сборки проекта.

### Сборка

1. Скомпилируйте проект:

   ```make install

   ```

2. Запустите исполняемый файл:

```
    ./MyCalculator

```

## Использование

### Графический интерфейс

Запустите программу и воспользуйтесь графическим интерфейсом для выполнения операций.

### Математические вычисления

Вы можете использовать класс CalcController для вычисления математических выражений в польской нотации:

```
#include "controller.h"

int main() {
    MyCalculator::CalcController calc;
    double result = calc.CalculateExpression("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```

### Расчет кредита

Класс Credit позволяет рассчитывать аннуитетные и дифференцированные платежи:

```
MyCalculator::Credit::PaymentOutput output;
calc.CalculateCredit(100000, 12, 5.5, 1, output);

std::cout << "Total Payment: " << output.total_payment << std::endl;
std::cout << "First Payment: " << output.first_payment << std::endl;
std::cout << "Last Payment: " << output.last_payment << std::endl;
std::cout << "Overpayment: " << output.overpayment << std::endl;

```

### Расчет депозита

Класс Deposit поддерживает различные настройки депозитов:

```

MyCalculator::Deposit::DepositOutput output;
calc.CalculateDeposit(10000, 12, 3.5, 1, 1, 2, 1, 500, 1, 200, output);

std::cout << "Result: " << output.result << std::endl;
std::cout << "Accrued Interest: " << output.accrued_interest << std::endl;
std::cout << "Tax Withheld: " << output.tax_with << std::endl;

```

## Структура проекта

- model: Содержит реализации моделей калькулятора кредита и депозита.
- controller: Содержит контроллер для взаимодействия с моделями.
- include: Заголовочные файлы для различных классов проекта.
- tests: Тесты для проверки корректности работы проекта.
