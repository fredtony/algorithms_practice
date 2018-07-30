#include <iostream>
#include <vector>

using namespace std;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
    int n = a.size(), m = b.size(), p = c.size(), val;
    int dist[p+1][m+1][n+1];
    for (int i=0; i<=p; ++i) {
        for (int j=0; j<=m; ++j)
           dist[i][j][0] = 0; 
    }
    for (int j=0; j<=m; ++j) {
        for (int k=0; k<=n; ++k)
           dist[0][j][k] = 0; 
    }
    for (int i=0; i<=p; ++i) {
        for (int k=0; k<=n; ++k)
           dist[i][0][k] = 0; 
    }
    for (int i=1; i<=p; ++i) {
        for (int j=1; j<=m; ++j) {
            for (int k=1; k<=n; ++k) {
                val = (int)((a[k-1] == b[j-1]) && (a[k-1] == c[i-1]));
                dist[i][j][k] = max(max(max(max(max(max(dist[i-1][j-1][k-1] + val, dist[i][j-1][k-1]), dist[i-1][j][k-1]), dist[i-1][j-1][k]), dist[i][j][k-1]), dist[i][j-1][k]), dist[i-1][j][k]);
            }
        }
    }
    return dist[p][m][n];
}

int main() {
    size_t an;
    cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        cin >> a[i];
    }
    size_t bn;
    cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        cin >> b[i];
    }
    size_t cn;
    cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        cin >> c[i];
    }
    cout << lcs3(a, b, c) << endl;
}
