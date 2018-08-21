#include <iostream>
#include <vector>

using namespace std;

int optimal_weight(int W, const vector<int> &w) {
    int** weights = new int*[w.size()+1];
    for(int i = 0; i <= w.size(); ++i)
        weights[i] = new int[W+1];
    // int weights[][W+1], val;
    int val;
    for (int i = 0; i <= w.size(); ++i)
        weights[i][0] = 0;
    for (int j = 1; j <= W; ++j)
        weights[0][j] = 0;
    for (int i = 1; i <= w.size(); ++i) {
        val = w[i-1];
        // cout << val << "   ";
        for (int j = 1; j <= W; ++j) {
            if ((val + weights[i-1][j-val] > j) || (j < val))
                weights[i][j] = weights[i-1][j];
            else
                weights[i][j] = max(max(weights[i-1][j-val] + val, weights[i-1][j]), weights[i][j-1]);
            // cout << weights[i][j] << ' ';
        }
        // cout << endl;
    }
    return weights[w.size()][W];
}

int main() {
    int n, W;
    cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    cout << optimal_weight(W, w) << '\n';
    return 0;
}
