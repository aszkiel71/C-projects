#include <stdio.h>

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

int main() {
  int a, b;
  printf("Enter 2 ints : \n");
  scanf("%d %d", &a, &b);
  printf("GCD of %d and %d is %d", a, b, gcd(a, b));
  return 0;
}
