#include <iostream>
#include <cassert>
using namespace std;

unsigned long long get_fibonacci_huge_naive(unsigned long long n, unsigned long long m) {
    if (n <= 1)
        return n;

    unsigned long long previous = 0;
    unsigned long long current  = 1;

    for (unsigned long long i = 0; i < n - 1; ++i) {
        unsigned long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

unsigned long long get_fibonacci_huge_fast(unsigned long long n, unsigned long long m) {
    bool no_pattern = true;
    unsigned long long len_fibs = (n < 100 ? n : 100);
    unsigned long long * fibs = new unsigned long long [len_fibs];
    fibs[0] = 0;
    fibs[1] = 1;
    unsigned long long num1 = 0, num2 = 1, fib = 1, split_idx = 0;
    for (unsigned long long i = 2; i <= n and no_pattern; ++i) {
        if (i >= len_fibs) {
            unsigned long long * old_fibs = fibs;
            fibs = new unsigned long long [len_fibs * 2];
            for (unsigned long long j = 0; j < len_fibs; ++j)
                fibs[j] = old_fibs[j];
            len_fibs *= 2;
            delete[] old_fibs;
        }

        fib = (num1 + num2) % m;
        num1 = num2;
        num2 = fib;
        fibs[i] = fib;

        if ((i+1)%2 == 0) {
            split_idx = (i+1)/2;
            no_pattern = false;
            for (unsigned long long j=0; j<split_idx; ++j) {
                if (fibs[j] != fibs[j+split_idx]) {
                    no_pattern = true;
                    break;
                }
            }
            if (!no_pattern) {
                return fibs[n % split_idx];
            }
        }
    }
    return fibs[n];
}

void test_solution() {
    assert(get_fibonacci_huge_fast(239, 1000) == 161);
    assert(get_fibonacci_huge_fast(2816213588, 239) == 151);
    for (int a = 2; a < 30; ++a) {
        for (int b = 2; b < 20; ++b) {
            assert(get_fibonacci_huge_fast(a, b) == get_fibonacci_huge_naive(a, b));
        }
    }
}

int main() {
    unsigned long long n, m;
    cin >> n >> m;

    // test_solution();
    cout << get_fibonacci_huge_fast(n, m) << endl;
}
