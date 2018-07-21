#include <iostream>
#include <vector>

using namespace std;

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
    long long number_of_inversions = 0;
    if (right <= left + 1) return number_of_inversions;
    size_t ave = left + (right - left) / 2;
    number_of_inversions += get_number_of_inversions(a, b, left, ave);
    number_of_inversions += get_number_of_inversions(a, b, ave, right);
    int j = left, k = ave;
    for (int i = left; i < right; ++i) {
        int l = a[j], r = a[k];
        if ((l <= r and j != ave) or k == right) {
            b[i] = l;
            j++;
        }
        else {
            b[i] = r;
            k++;
            number_of_inversions += (ave - j);
        }
    }
    for (int i = left; i < right; ++i) {
        a[i] = b[i];
    }
    return number_of_inversions;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        cin >> a[i];
    }
    vector<int> b(a.size());
    cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
