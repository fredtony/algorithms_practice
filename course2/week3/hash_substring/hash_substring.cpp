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

void print_occurrences(const vector<int>& output) {
    for (int i = (int)output.size()-1; i >= 0; --i)
        cout << output[i] << " ";
    cout << "\n";
}

vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    static const ull prime = 1000000007;
    vector<int> ans;
    ull pattern_hash = 0, input_hash = 0;
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        pattern_hash = (pattern_hash * 26) % prime;
        pattern_hash = (pattern_hash + (ull)(s[i] - 'A')) % prime;
    }
    // cout << "pattern hash: " << pattern_hash << std::endl;
    for (int i = (int)t.size() - 1; i >= (int)(t.size() - s.size()); --i) {
        input_hash = (input_hash * 26) % prime;
        input_hash = (input_hash + (ull)(t[i] - 'A')) % prime;
    }
    // cout << "text hash: " << input_hash << std::endl;
    if (pattern_hash == input_hash) {
        if (t.compare(t.size() - s.size(), s.size(), s) == 0)
            ans.push_back((int)(t.size() - s.size()));
    }
    for (int i = (int)t.size() - s.size() - 1; i >= 0; --i) {
        input_hash = (input_hash - (ull)(t[i+s.size()] - 'A') * (ull)pow(26, s.size()-1) + prime) % prime;
        input_hash = (input_hash * 26) % prime;
        input_hash = (input_hash + (ull)(t[i] - 'A')) % prime;
        // cout << "text hash: " << input_hash << std::endl;
        if (pattern_hash == input_hash)
            if (t.compare(i, s.size(), s) == 0)
                ans.push_back((int)i);
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
