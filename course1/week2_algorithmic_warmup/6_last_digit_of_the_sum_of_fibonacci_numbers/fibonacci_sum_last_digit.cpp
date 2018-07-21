#include <iostream>
#include <cassert>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

int fibonacci_sum_fast(long long n) {
    int fibs [60] = {0, 1};
    int fibsums [60] = {0, 1};
    int num1 = 0, num2 = 1, fib = 1;
    for (int i = 2; i < 60 and i <= n; ++i) {
        fib = (num1 + num2) % 10;
        num1 = num2;
        num2 = fib;
        fibs[i] = fib;
        fibsums[i] = (fibsums[i-1] + fib) % 10;
    }
    return fibsums[n%60];
}

void test_solution() {
    assert(fibonacci_sum_fast(3) == 4);
    assert(fibonacci_sum_fast(100) == 5);
    for (int a = 2; a < 20; ++a) {
        assert(fibonacci_sum_fast(a) == fibonacci_sum_naive(a));
    }
}

int main() {
    long long n = 0;
    // test_solution();
    std::cin >> n;
    std::cout << fibonacci_sum_fast(n);
}
