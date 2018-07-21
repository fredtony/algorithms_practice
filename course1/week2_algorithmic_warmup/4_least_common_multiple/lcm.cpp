#include <iostream>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int gcd_fast(int a, int b) {
  int num1 = (((a) > (b)) ? (a) : (b));
  int num2 = (((a) < (b)) ? (a) : (b));
  if (num2 == 0) return num1;
  else {
    return gcd_fast(num2, num1 % num2);
  }
}

long long lcm_fast(int a, int b) {
	long long mult = a * b;
	long long gcd = gcd_fast(a, b);
	return mult / gcd;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
