#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <cmath>

using std::string;
using std::cout;
using std::cin;
using std::vector;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const vector<long long>& output) {
    for (long long i = (long long)output.size()-1; i >= 0; --i)
        cout << output[i] << " ";
    cout << "\n";
}

vector<long long> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    static const ull prime = 1000000007, mult = 100;
    vector<long long> ans;
    ull pattern_hash = 0, input_hash = 0, y = 1;
    for (long long i = (long long)s.size() - 1; i >= 0; --i) {
        y = (y * mult) % prime;
        pattern_hash = (pattern_hash * mult) % prime;
        pattern_hash = (pattern_hash + (ull)(s[i])) % prime;
    }
    // cout << "pattern hash: " << pattern_hash << std::endl;
    for (long long i = (long long)t.size() - 1; i >= (long long)(t.size() - s.size()); --i) {
        input_hash = (input_hash * mult) % prime;
        input_hash = (input_hash + (ull)(t[i])) % prime;
    }
    // cout << "text hash: " << input_hash << std::endl;
    if (pattern_hash == input_hash) {
        if (t.compare(t.size() - s.size(), s.size(), s) == 0)
            ans.push_back((long long)(t.size() - s.size()));
    }
    for (long long i = (long long)(t.size() - s.size() - 1); i >= 0; --i) {
        input_hash = (((input_hash * mult + prime - ((ull)(t[i+s.size()] * y) % prime)) % prime) + (ull)(t[i]) + prime) % prime;
        // cout << "text hash " << i << ":\t" << input_hash << std::endl;
        if (pattern_hash == input_hash)
            if (t.compare(i, s.size(), s) == 0)
                ans.push_back((long long)i);
    }
    return ans;
}

// vector<long long> get_occurrences_naive(const Data& input) {
// }

// void test_solution() {
//     long long num_checks = 1000, pattern_size = 10, text_size = 1000;
//     for (long long i = 0; i < num_checks; ++i) {
//     }
// }


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
