#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// long long binary_search_mod(const vector<int> &a, long long x, long long left=0, long long right=-1) {
//     if (right == -1)
//         right = (long long)a.size()-1;
//     if (right - left == 0) {
//         if (x >= a[right])
//             return right;
//         else
//             return right-1;
//     }
//     else if (right - left == 1) {
//         if (x >= a[right])
//             return right;
//         if (x >= a[left])
//             return left;
//         else
//             return left-1;
//     }
//     else {
//         long long elem = left + (right - left) / 2;
//         if (a[elem] == x)
//             return elem;
//         else if (x < a[elem])
//             return binary_search_mod(a, x, left=left, right=elem-1);
//         else
//             return binary_search_mod(a, x, left=elem+1, right=right);
//     }
    
// }

vector<long long> fast_count_segments(vector<long long> starts, vector<long long> ends, vector<long long> points) {
    vector<long long> cnt(points.size());
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());
    vector<long long>::iterator l, r;
    // long long l, r;
    for (long long i = 0; i < cnt.size(); ++i) {
        l = upper_bound(starts.begin(), starts.end(), points[i]);
        r = lower_bound(ends.begin(), ends.end(), points[i]);
        // l = binary_search_mod(starts, points[i]) + 1;
        // r = binary_search_mod(ends, points[i]);
        // if (points[i] != ends[r-1] or r == -1)
        //     r++;
        cnt[i] = (long long)(l - starts.begin()) - (long long)(r - ends.begin());
    }
    return cnt;
}

vector<long long> naive_count_segments(vector<long long> starts, vector<long long> ends, vector<long long> points) {
    vector<long long> cnt(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < starts.size(); j++) {
            cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
    return cnt;
}

// void test_solution() {
//     long long seed = 0;
//     default_random_engine eng (seed);
//     uniform_int_distribution<long long> distr(-100000000, 100000000); // define the range

//     for(int n=0; n<100; ++n) {
//         long long points_len = 50000;
//         long long segments_len = 50000;
//         vector<long long> starts(segments_len), ends(segments_len), points(points_len);
//         long long tmp;
//         for (long long i = 0; i < segments_len; ++i) {
//             tmp = distr(eng);
//             starts[i] = distr(eng);
//             if (tmp < starts[i]) {
//                 ends[i] = starts[i];
//                 starts[i] = tmp;
//             } else {
//                 ends[i] = tmp;
//             }
//         }
//         for (long long i = 0; i < points_len; ++i) {
//             points[i] = distr(eng);
//         }
//         vector<long long> cnt1 = naive_count_segments(starts, ends, points);
//         vector<long long> cnt2 = fast_count_segments(starts, ends, points);
        
//         for (long long i = 0; i < cnt1.size(); ++i) {
//             if (cnt1[i] != cnt2[i]) {
//                 cout << "Error at index " << i << " with naive " << cnt1[i] << " and fast " << cnt2[i] << endl;
//                 cout << "Segments:\n";
//                 for (long long j = 0; j < starts.size(); ++j) {
//                     cout << starts[j] << '/' << ends[j] << ' ';
//                 }
//                 cout << "\n\n";
//                 for (long long j = 0; j < starts.size(); ++j) {
//                     cout << points[j] << ' ';
//                 }
//                 cout << "\n\n";
//                 for (long long j = 0; j < cnt1.size(); ++j) {
//                     cout << cnt1[j] << ' ';
//                 }
//                 cout << "\n\n";
//                 for (long long j = 0; j < cnt2.size(); ++j) {
//                     cout << cnt2[j] << ' ';
//                 }
//                 return;
//             }
//         }
//     }
//     cout << "All tests passed!" << endl;
// }

int main() {
    // test_solution();
    long long n, m;
    cin >> n >> m;
    vector<long long> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
        cin >> starts[i] >> ends[i];
    }
    vector<long long> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        cin >> points[i];
    }
    //use fast_count_segments
    // vector<long long> cnt = naive_count_segments(starts, ends, points);
    vector<long long> cnt = fast_count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt.size(); i++) {
        cout << cnt[i] << ' ';
    }
    return 0;
}
