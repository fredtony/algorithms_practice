#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int optimal_weight(int W, vector<int> &w) {
    int w_size = (int)w.size();
    int weights[w_size+1][W+1], val;
    for (int i=0; i<=w_size; ++i)
        weights[i][0] = 0;
    for (int j=1; j<=W; ++j)
        weights[0][j] = 0;
    for (int i=1; i<=w_size; ++i) {
        val = w[i-1];
        // cout << val << "   ";
        for (int j=1; j<=W; ++j) {
            if ((val + weights[i-1][j-val] > j) || (j < val))
                weights[i][j] = weights[i-1][j];
            else
                weights[i][j] = max(max(weights[i-1][j-val] + val, weights[i-1][j]), weights[i][j-1]);
            // cout << weights[i][j] << ' ';
        }
        // cout << endl;
    }
    int col = W;
    for (int i=w_size-1; i>=0; --i) {
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

void print_vect(const vector<int> x) {
    for (int i=0; i<(int)x.size(); ++i)
        cout << x[i] << ' ';
    cout << " (" << x.size() << ')' << endl;
}

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
