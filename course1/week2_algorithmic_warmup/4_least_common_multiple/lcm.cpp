#include <iostream>

unsigned long long lcm_naive(unsigned long a, unsigned long b) {
	for (unsigned long long l = 1; l <=  a * b; ++l)
		if (l % a == 0 && l % b == 0)
			return l;

	return (unsigned long long) a * b;
}

unsigned long long gcd_fast(unsigned long long a, unsigned long long b) {
	unsigned long long num1 = (((a) > (b)) ? (a) : (b));
	unsigned long long num2 = (((a) < (b)) ? (a) : (b));
	if (num2 == 0) return num1;
	else {
		return gcd_fast(num2, num1 % num2);
	}
}

unsigned long long lcm_fast(unsigned long long a, unsigned long long b) {
	unsigned long long mult = a * b;
	unsigned long long gcd = gcd_fast(a, b);
	return mult / gcd;
}

int main() {
	unsigned long long a, b;
	std::cin >> a >> b;
	std::cout << lcm_fast(a, b) << std::endl;
	return 0;
}
