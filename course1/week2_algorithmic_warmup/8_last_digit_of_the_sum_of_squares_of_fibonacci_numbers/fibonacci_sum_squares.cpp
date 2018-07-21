#include <iostream>
#include <cassert>

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}

long long fibonacci_sum_squares_fast(long long n) {
    long long fibs [60] = {0, 1};
    long long num1 = 0, num2 = 1, fib = 1;
    for (int i = 2; i < 60; ++i) {
        fib = (num1 + num2) % 10;
        num1 = num2;
        num2 = fib;
        fibs[i] = fib;
    }
    return (fibs[n%60] * fibs[(n+1)%60]) % 10;
}

void test_solution() {
    assert(fibonacci_sum_squares_fast(7) == 3);
    assert(fibonacci_sum_squares_fast(73) == 1);
    assert(fibonacci_sum_squares_fast(1234567890) == 0);
    for (int a = 2; a < 40; ++a) {
        assert(fibonacci_sum_squares_fast(a) == fibonacci_sum_squares_naive(a));
    }
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_squares_fast(n);
    //test_solution();
    //std::cout << "Done.";
}
