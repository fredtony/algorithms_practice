#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int MaxPairwiseProduct(const vector<long long>& numbers) {
    int n = numbers.size();

    long long num1 = max(numbers[0], numbers[1])
    long long num2 = min(numbers[0], numbers[1])

    for (int i = 2; i < n; ++i) {
        if (numbers[i] > num1) { num2 = num1; num1 = numbers[i]; }
        else if (numbers[i] > num2) num2 = numbers[i];
    }
    return num1 * num2;
}

int main() {
    int n;
    cin >> n;
    vector<long long> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    long long result = MaxPairwiseProduct(numbers);
    cout << result << "\n";
    return 0;
}
