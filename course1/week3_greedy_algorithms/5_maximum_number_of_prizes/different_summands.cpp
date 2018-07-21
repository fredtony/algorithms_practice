#include <iostream>
#include <vector>

using namespace std;

vector<int> optimal_summands(int n) {
    vector<int> summands;
    summands.push_back(1);
    int next = 2, num_sum = 1;
    while ( num_sum < n ) {
        if ( num_sum + next <= n ) {
            summands.push_back(next);
            num_sum += next;
            ++next;
        }
        else {
            int diff = n - num_sum;
            summands[summands.size()-1] += diff;
            num_sum += diff;
        }
    }
    return summands;
}

int main() {
    int n;
    cin >> n;
    vector<int> summands = optimal_summands(n);
    cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        cout << summands[i] << ' ';
    }
}
