#include <iostream>
#include <vector>

using namespace std;

int lcs2(vector<int> &a, vector<int> &b) {
    int n = a.size(), m = b.size(), val;
    int dist[m+1][n+1] = {0};
    for (int i=0; i<=m; ++i)
        dist[i][0] = 0;
    for (int j=1; j<=n; ++j)
        dist[0][j] = 0;
    for (int i=1; i<=m; ++i) {
        for (int j=1; j<=n; ++j) {
            val = (int)(a[j-1] == b[i-1]);
            dist[i][j] = max(max(dist[i-1][j-1] + val, dist[i][j-1]), dist[i-1][j]);
        }
    }
    return dist[m][n];
}

int main() {
    size_t n;
    cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++) {
        cin >> a[i];
    }

    size_t m;
    cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) {
        cin >> b[i];
    }

    cout << lcs2(a, b) << endl;
}
