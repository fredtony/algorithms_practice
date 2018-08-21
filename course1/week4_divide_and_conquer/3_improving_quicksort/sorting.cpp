#include <iostream>
#include <vector>
#include <cstdlib>
#include <tuple>
#include <random>

using namespace std;

// long long partition2(vector<long long> &a, long long l, long long r) {
//     long long x = a[l];
//     long long j = l;
//     for (long long i = l + 1; i <= r; i++) {
//         if (a[i] <= x) {
//             j++;
//             swap(a[i], a[j]);
//         }
//     }
//     swap(a[l], a[j]);
//     return j;
// }

tuple<long long, long long> partition3(vector<long long> &a, long long l, long long r) {
    long long x = a[l];
    long long j = l, k = l;
    for (long long i = l + 1; i <= r; i++) {
        if (a[i] == x) {
            k++;
            swap(a[i], a[k]);
        } else if (a[i] < x) {
            j++;
            k++;
            if (j != k) swap(a[i], a[j]);
            swap(a[i], a[k]);
        }
    }
    swap(a[l], a[j]);
    long long lower = max(j - 1, l), upper = min(k + 1, r);
    return make_tuple(lower, upper);
}

// void randomized_quick_sort(vector<long long> &a, long long l, long long r) {
//     if (l >= r) {
//         return;
//     }

//     long long k = l + ((long long)rand()) % (r - l + 1);
//     swap(a[l], a[k]);
//     long long m = partition2(a, l, r);

//     randomized_quick_sort(a, l, m - 1);
//     randomized_quick_sort(a, m + 1, r);
// }

void improved_quick_sort(vector<long long> &a, long long l, long long r) {
    if (l >= r) {
        return;
    }

    long long k = l + ((long long)rand()) % (r - l + 1);
    swap(a[l], a[k]);
    tuple<long long, long long> middle = partition3(a, l, r);

    improved_quick_sort(a, l, get<0>(middle));
    improved_quick_sort(a, get<1>(middle), r);
}

// void test_solution() {
//     long long seed = 0;
//     default_random_engine eng (seed);
//     uniform_int_distribution<long long> distr(1, 1000000000); // define the range

//     for(int n=0; n<100; ++n) {
//         long long num = 10000;
//         vector<long long> rand_vect1(num), rand_vect2(num);
//         for (long long i = 0; i < num; ++i) {
//             long long samp = distr(eng);
//             rand_vect1[i] = samp;
//             rand_vect2[i] = samp;
//         }
//         randomized_quick_sort(rand_vect1, 0, rand_vect1.size() - 1);
//         cout << "quicksort complete." << endl;
//         improved_quick_sort(rand_vect2, 0, rand_vect2.size() - 1);
//         cout << "improved quicksort complete." << endl;
        
//         for (long long i = 0; i < rand_vect1.size(); ++i) {
//             if (rand_vect1[i] != rand_vect2[i]) {
//                 cout << "Error at index " << i << " with reg " << rand_vect1[i] << "and new " << rand_vect2[i] << endl;
//                 for (long long j = 0; j < rand_vect1.size(); ++j) {
//                     cout << rand_vect1[j] << ' ';
//                 }
//                 cout << endl << endl;
//                 for (long long j = 0; j < rand_vect2.size(); ++j) {
//                     cout << rand_vect2[j] << ' ';
//                 }
//                 cout << endl;
//                 return;
//             }
//         }
//     }
// }

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        cin >> a[i];
    }
    // randomized_quick_sort(a, 0, a.size() - 1);
    improved_quick_sort(a, 0, a.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        cout << a[i] << ' ';
    }
    // test_solution();
    return 0;
}
