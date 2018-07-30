#include <iostream>
#include <string>

using namespace std;

int edit_distance(const string &str1, const string &str2) {
	int n = str1.length(), m = str2.length(), val;
	int dist[m+1][n+1] = {n+m};
	dist[0][0] = 0;
	for (int i=1; i<=n; ++i)
		dist[0][i] = dist[0][i-1] + 1;
	for (int j=1; j<=m; ++j)
		dist[j][0] = dist[j-1][0] + 1;
	for (int i=1; i<=m; ++i) {
		for (int j=1; j<=n; ++j) {
			val = (int)(str2[i-1] != str1[j-1]);
			dist[i][j] = min(min(dist[i-1][j-1] + val, dist[i][j-1]+1), dist[i-1][j]+1);
		}
	}
	return dist[m][n];
}

int main() {
	string str1;
	string str2;
	cin >> str1 >> str2;
	cout << edit_distance(str1, str2) << endl;
	return 0;
}
