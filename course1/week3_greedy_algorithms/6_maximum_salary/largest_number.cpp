#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool my_compare(string i, string j) {
    string x = i + j;
    string y = j + i;
    return stoi(x) > stoi(y);
}

string largest_number(vector<string> a) {
    sort(a.begin(), a.end(), my_compare);
    stringstream ret;
    for (size_t i = 0; i < a.size(); i++) {
        ret << a[i];
    }
    string result;
    ret >> result;
    return result;
}

int main() {
    int n;
    cin >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        cin >> a[i];
    }
    cout << largest_number(a);
    return 0;
}
