#include <algorithm>
#include <iostream>
#include <vector>
// #include <iterator>

using namespace std;

// template <class T>
// T get_remove_max(vector<T>& arr) {
//     unsigned int i = distance(arr.begin(), max_element(arr.begin(), arr.end()));
//     T val = arr[i];
//     if (i != arr.size()-1) {
//         arr[i] = arr[arr.size()-1];
//     }
//     arr.pop_back();
//     return val;
// }

long long max_dot_product(vector<int> a, vector<int> b) {
    long long result = 0;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0; i < (int)a.size(); i++) {
        result += (long long) a[i] * (long long) b[i];
    }
    return result;
}

int main() {
    size_t n;
    cin >> n;
    vector<int> a(n), b(n);
    for (size_t i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (size_t i = 0; i < n; i++) {
        cin >> b[i];
    }
    cout << max_dot_product(a, b) << endl;
}
