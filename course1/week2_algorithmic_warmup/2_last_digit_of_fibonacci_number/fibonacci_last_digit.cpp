#include <iostream>
// #include <cassert>

using namespace std;

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;
    int tmp_previous = 0;

    for (int i = 0; i < n - 1; ++i) {
        tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int get_fibonacci_last_digit_fast(int n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    int num1 = 0;
    int num2 = 1;
    int fib = 0;
    for (int i=2; i <= n; ++i) {
        fib = (num1 + num2) % 10;
        num1 = num2;
        num2 = fib;
    }
    return fib;
}

// void test_solution() {
//     assert(get_fibonacci_last_digit_fast(3) == 2);
//     assert(get_fibonacci_last_digit_fast(10) == 5);
//     assert(get_fibonacci_last_digit_fast(331) == 9);
//     for (int n = 0; n < 20; ++n)
//         assert(get_fibonacci_last_digit_fast(n) == get_fibonacci_last_digit_naive(n));
// }

int main() {
    int n;
    cin >> n;
    // int c = get_fibonacci_last_digit_naive(n);
    // test_solution();
    cout << get_fibonacci_last_digit_fast(n) << '\n';
    }
