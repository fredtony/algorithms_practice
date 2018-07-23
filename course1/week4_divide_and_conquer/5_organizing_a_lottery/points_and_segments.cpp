#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int binary_search_mod(const vector<int> &a, int x, int left=0, int right=-1) {
    if (right == -1)
        right = (int)a.size()-1;
    if (right - left == 0) {
        if (x >= a[right])
            return right;
        else
            return right-1;
    }
    else if (right - left == 1) {
        if (x >= a[right])
            return right;
        if (x >= a[left])
            return left;
        else
            return left-1;
    }
    else {
        int elem = left + (right - left) / 2;
        if (a[elem] == x)
            return elem;
        else if (x < a[elem])
            return binary_search_mod(a, x, left=left, right=elem-1);
        else
            return binary_search_mod(a, x, left=elem+1, right=right);
    }
    
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    int len = (int)points.size();
    vector<int> cnt(len);
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());
    int l, r;
    for (int i = 0; i < len; ++i) {
        l = binary_search_mod(starts, points[i]) + 1;
        r = binary_search_mod(ends, points[i]);
        if (points[i] != ends[r-1] or r == -1)
            r++;
        cnt[i] = l - r;
    }
    return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < starts.size(); j++) {
            cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
    return cnt;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
        cin >> starts[i] >> ends[i];
    }
    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        cin >> points[i];
    }
    //use fast_count_segments
    // vector<int> cnt = naive_count_segments(starts, ends, points);
    vector<int> cnt = fast_count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt.size(); i++) {
        cout << cnt[i] << ' ';
    }
}

