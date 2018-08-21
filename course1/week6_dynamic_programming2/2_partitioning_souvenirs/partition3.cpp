#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// void print_vect(const vector<int> x) {
//     for (int i=0; i<(int)x.size(); ++i)
//         cout << x[i] << ' ';
//     cout << " (" << x.size() << ')' << endl;
// }

int optimal_weight(int W, vector<int> &w) {
    int w_size = (int)w.size(), val;
    int** weights = new int*[w_size + 1];
    for(int i = 0; i <= w.size(); ++i)
        weights[i] = new int[W+1];
    for (int i = 0; i <= w_size; ++i)
        weights[i][0] = 0;
    for (int j = 1; j <= W; ++j)
        weights[0][j] = 0;
    for (int i = 1; i <= w_size; ++i) {
        val = w[i-1];
        // cout << val << "   ";
        for (int j = 1; j <= W; ++j) {
            if ((val + weights[i-1][j-val] > j) || (j < val))
                weights[i][j] = weights[i-1][j];
            else
                weights[i][j] = max(max(weights[i-1][j-val] + val, weights[i-1][j]), weights[i][j-1]);
            // cout << weights[i][j] << ' ';
        }
        // cout << endl;
    }
    int col = W;
    for (int i = w_size - 1; i > 0; --i) {
        // cout << "col=" << col << endl;
    	if (col == 0)
    		break;
    	val = w[i-1];
    	if (val > col)
    		continue;
    	if (weights[i][col] == weights[i-1][col-val] + val) {
    		col -= val;
    		swap(w[i-1], w[w.size()-1]);
    		w.pop_back();
    	}
    	else if (weights[i][col] == weights[i][col-1]) {
    		--col;
    		++i;
    	}
    }
    return weights[w_size][W];
}

/*
Tried to solve this by sorting and essentially taking largest
pieces out that make up total/3, then do it again, and hope that
the 2nd and 3rd partitions work out with this greedy choice. I
believe that this works because larger values will get used
first since they are more difficult to piece together with other
values, then the smaller values are left to the end. If 
this solution does not work, it might be useful to run
optimal_weight once and find the various solutions with
recursion (i.e. start from weights[w_size][W] and work both one
up if the val is the same and diagonally back if
weights[i][col] == weights[i-1][col-val] + val, both of which
can give viable solutions), put each solution into a hash table,
and then check to see if there is a solutions by choosing 3
such that they contain all of the elements when unioned
*/
int partition3(vector<int> &A, int total) {
	if (total % 3 != 0)
		return 0;
	total = total / 3;
	sort(A.begin(), A.end());
	// print_vect(A);
	int tmp = optimal_weight(total, A);
	// cout << "total 1: " << tmp << endl;
	if (tmp != total)
		return 0;
	sort(A.begin(), A.end());
	// print_vect(A);
	tmp = optimal_weight(total, A);
	// cout << "total 2: " << tmp << endl;
	if (tmp != total)
		return 0;
	// print_vect(A);
	return 1;
}

int main() {
	int n, total = 0;
	cin >> n;
	vector<int> A(n);
	for (size_t i = 0; i < A.size(); ++i) {
		cin >> A[i];
		total += A[i];
	}
	cout << partition3(A, total) << '\n';
}
