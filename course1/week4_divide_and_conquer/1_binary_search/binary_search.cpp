#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int binary_search(const vector<int> &a, int x, int left=0, int right=-1) {
    if (right == -1)
        right = (int)a.size()-1;
    if (right - left == 0) {
        if (a[right] == x)
            return right;
        else
            return -1;
    }
    else if (right - left == 1) {
        if (a[left] == x)
            return left;
        else if (a[right] == x)
            return right;
        else
            return -1;
    }
    else {
        int elem = left + (right - left) / 2;
        if (a[elem] == x)
            return elem;
        else if (x < a[elem])
            return binary_search(a, x, left=left, right=elem-1);
        else
            return binary_search(a, x, left=elem+1, right=right);
    }
    
}

int linear_search(const vector<int> &a, int x) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == x) return i;
    }
    return -1;
}

void test_solution() {
    return;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    for (int i = 0; i < m; ++i) {
        //replace with the call to binary_search when implemented
        // cout << linear_search(a, b[i]) << ' ';
        cout << binary_search(a, b[i]) << ' ';
    }
}

