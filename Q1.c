#include <stdio.h>

double calculateRepayment(double loan, double rate, int years) {
    if (loan <= 0 || years == 0)
        return 0;

    double updatedLoan = loan + loan * rate;
    double installment = 30000;
    double remaining = updatedLoan - installment;

    if (remaining < 0)
        remaining = 0;

    int currentYear = 4 - years;
    printf("Year %d: Remaining loan = %.2f\n", currentYear, remaining);

    return installment + calculateRepayment(remaining, rate, years - 1);
}

int main() {
    double loan = 100000;
    double rate = 0.05;
    int years = 3;

    double total = calculateRepayment(loan, rate, years);

    printf("\nTotal repayment over %d years = %.2f\n", years, total);

    return 0;
}
