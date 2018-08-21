#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>

using namespace std;

struct maj_element {
    int left, right, maj, maj_count;
};

maj_element get_majority_element(vector<int> &a, maj_element overall) {
    if (overall.left == overall.right) {
        overall.maj = -1;
        return overall;
    }
    if (overall.left + 1 == overall.right) {
        overall.maj = a[overall.left];
        overall.maj_count = 1;
        return overall;
    }
    int vote = (overall.right - overall.left) / 2;
    int split = overall.left + vote;
    
    maj_element left;
    left.left = overall.left;
    left.right = split;
    left = get_majority_element(a, left);
    if (left.maj >= 0) {
        int maj_count = left.maj_count;
        for ( int i = split ; i < overall.right ; ++i ) {
            if (a[i] == left.maj) {
                maj_count++;
            }
        }
        if (maj_count > vote) {
            overall.maj = left.maj;
            overall.maj_count = maj_count;
            return overall;
        }
    }
    maj_element right;
    right.left = split;
    right.right = overall.right;
    right = get_majority_element(a, right);
    if (right.maj >= 0) {
        int maj_count = right.maj_count;
        for ( int i = overall.left ; i < split ; ++i ) {
            if (a[i] == right.maj) {
                maj_count++;
            }
        }
        if (maj_count > vote) {
            overall.maj = right.maj;
            overall.maj_count = maj_count;
            return overall;
        }
    }
    overall.maj = -1;
    return overall;
}

int get_majority_element_fast(vector<int> &b) {
    unordered_map<int, int> counts;
    int total = 0;
    for (int i=0; i < b.size(); ++i) {
        total++;
        if (counts.find(b[i]) == counts.end())
            counts[b[i]] = 1;
        else
            counts[b[i]] = counts[b[i]] + 1;
    }
    int vote = total / 2;
    unordered_map<int, int>:: iterator itr;
    for (itr = counts.begin(); itr != counts.end() ; itr++) {
        if ((itr->second) > vote)
            return 1;
    }
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        cin >> a[i];
    }
    // maj_element overall;
    // overall.left = 0;
    // overall.right = a.size();
    // overall = get_majority_element(a, overall);
    // cout << (overall.maj != -1) << '\n';
    cout << get_majority_element_fast(a) << '\n';
}
