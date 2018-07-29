#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> optimal_sequence(int n) {
    vector<int> sequence, calc(n+1, n+1);
    calc[0] = 0;
    for (int i=0; i<n; ++i) {
        calc[i+1] = min(calc[i+1], calc[i] + 1);
        if (2*i <= n)
            calc[2*i] = min(calc[2*i], calc[i] + 1);
        if (3*i <= n)
            calc[3*i] = min(calc[3*i], calc[i] + 1);
    }
    sequence.push_back(n);
    while (n > 1) {
        if (calc[n] == calc[n-1]+1)
            n--;
        else if ((n%2 == 0) && (calc[n] == calc[n/2]+1))
            n /= 2;
        else
            n /= 3;
        sequence.push_back(n);
    }
    reverse(sequence.begin(), sequence.end());
    return sequence;
}

int main() {
    int n;
    cin >> n;
    vector<int> sequence = optimal_sequence(n);
    cout << sequence.size() - 1 << endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        cout << sequence[i] << " ";
    }
}
