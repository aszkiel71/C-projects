#include <stdio.h>

long long power(int base, int exp) {
  long long res = 1;
  if (exp < 0) {
    printf("Error: Negative exponent not supported for integer result.\n");
    return -1;
  }
  if (exp == 0) return 1;
  if (exp == 1) return base;

  long long temp = power(base, exp / 2);
  if (exp % 2 == 0) {
    res = temp * temp;
  } else {
    res = base * temp * temp;
  }
  return res;
}

int main() {
  int base, exp;
  printf("Enter base and exponent (non-negative exponent): ");
  if (scanf("%d %d", &base, &exp) != 2 || exp < 0) {
    printf("Invalid input. Exponent must be non-negative.\n");
    return 1;
  }
  printf("%d^%d = %lld\n", base, exp, power(base, exp));
  return 0;
}
