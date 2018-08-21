#include <iostream>

using namespace std;

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_fast(int a, int b) {
  int num1 = (((a) > (b)) ? (a) : (b));
  int num2 = (((a) < (b)) ? (a) : (b));
  if (num2 == 0) return num1;
  else {
    return gcd_fast(num2, num1 % num2);
  }
}

// void test_solution() {
//     assert(gcd_fast(3, 6) == 3);
//     assert(gcd_fast(331, 662) == 331);
//     for (int a = 1; a < 20; ++a) {
//       for (int b = 1; b < 20, ++b)
//         assert(gcd_fast(a, b) == gcd_naive(a, b));
//     }
// }

int main() {
  int a, b;
  cin >> a >> b;
  // test_solution()
  cout << gcd_fast(a, b) << endl;
  return 0;
}