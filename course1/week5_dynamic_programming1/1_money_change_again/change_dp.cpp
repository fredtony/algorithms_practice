#include <iostream>
#include <vector>

using namespace std;

int get_change(int m) {
	vector<int> change(m+4, m+4);
	change[0] = 0;
	for (int i=0; i<m; ++i) {
		change[i+1] = min(change[i+1], change[i]+1);
		change[i+3] = min(change[i+3], change[i]+1);
		change[i+4] = min(change[i+4], change[i]+1);
	}
	return change[m];
}

int main() {
	int m;
	cin >> m;
	cout << get_change(m) << '\n';
}
