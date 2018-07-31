#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

// template <class myType>
// void print_vect(const vector<myType> x) {
//     for (int i=0; i<(int)x.size(); ++i)
//         cout << x[i] << '\t';
//     cout << " (" << x.size() << ')' << endl;
// }

long long eval(long long a, long long b, char op) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        assert(0);
    }
}

long long get_maximum_value(const string &exp) {
    int num = ((int)exp.size() + 1) / 2;
    vector<long long> nums;
    vector<char> ops;
    long long calc[num][num], val1, val2, min_val, max_val;
    nums.push_back((long long)(exp[0]-'0'));
    ops.push_back((char)exp[1]);
    calc[0][0] = nums[0];
    for (int j=1; j<num; ++j) {
        nums.push_back((long long)(exp[j*2]-'0'));
        ops.push_back((char)exp[j*2+1]);
        calc[j][j] = nums[j];
        for (int i=j-1; i>=0; --i) {
            val1 = eval(calc[i][i], calc[i+1][j], ops[i]);
            val2 = eval(calc[i][i], calc[j][i+1], ops[i]);
            min_val = (val1 < val2 ? val1 : val2);
            max_val = (val1 > val2 ? val1 : val2);
            for (int k=1; k<(j-i); ++k) {
                val1 = eval(calc[i][i+k], calc[i+1+k][j], ops[i+k]);
                if (val1 < min_val) min_val = val1;
                else if (val1 > max_val) max_val = val1;
                val1 = eval(calc[i][i+k], calc[j][i+1+k], ops[i+k]);
                if (val1 < min_val) min_val = val1;
                else if (val1 > max_val) max_val = val1;
                val1 = eval(calc[i+k][i], calc[i+1+k][j], ops[i+k]);
                if (val1 < min_val) min_val = val1;
                else if (val1 > max_val) max_val = val1;
                val1 = eval(calc[i+k][i], calc[j][i+1+k], ops[i+k]);
                if (val1 < min_val) min_val = val1;
                else if (val1 > max_val) max_val = val1;
            }
            calc[i][j] = max_val;
            calc[j][i] = min_val;
        }
    }
    // for (int i=0; i<num; ++i) {
    //     for (int j=0; j<num; ++j) {
    //         cout << calc[i][j] << '\t';
    //     }
    //     cout << endl;
    // }
    // print_vect(nums);
    // print_vect(ops);
    return calc[0][num-1];
}

int main() {
    string s;
    cin >> s;
    cout << get_maximum_value(s) << '\n';
    return 0;
}
