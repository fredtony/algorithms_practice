#include <iostream>
#include <cassert>

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;
    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

long long get_fibonacci_partial_sum_fast(long long from, long long to) {
    long long fibs [60] = {0, 1};
    long long num1 = 0, num2 = 1, fib = 1;
    for (int i = 2; i < 60; ++i) {
        fib = (num1 + num2) % 10;
        num1 = num2;
        num2 = fib;
        fibs[i] = fib;
    }

    long long fibsum = fibs[from%60];
    if (from%60 == to%60) return fibsum;
    for (long long i=from%60; i!=to%60; ++i) {
        fibsum = (fibsum + fibs[(i+1)%60]);
    }
    return fibsum%10;
}

void test_solution() {
    assert(get_fibonacci_partial_sum_fast(3, 7) == 1);
    assert(get_fibonacci_partial_sum_fast(10, 10) == 5);
    assert(get_fibonacci_partial_sum_fast(10, 200) == 2);
    for (int a = 2; a < 10; ++a) {
        for (int b = a+1; b < 20; ++b) {
            assert(get_fibonacci_partial_sum_fast(a, b) == get_fibonacci_partial_sum_naive(a, b));
        }
    }
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    // test_solution();
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
