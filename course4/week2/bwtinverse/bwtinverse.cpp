#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int const Letters = 5;

int idx(char letter) {
	switch (letter) {
		case '$': return 0; break;
		case 'A': return 1; break;
		case 'C': return 2; break;
		case 'G': return 3; break;
		case 'T': return 4; break;
		default: assert(false); return -1;
	}
}

vector<vector<int>> createFMIndex(const string& bwt) {
	vector<vector<int>> result;
	vector<int> row (Letters, 0);

	result.push_back(row);
	for (int i = 0; i < bwt.size(); ++i) {
		++row[idx(bwt[i])];
		result.push_back(row);
	}
	int count = 0;
	for (int i = 0; i < Letters; ++i) {
		row[i] = count;
		count += result[bwt.size()][i];
	}
	result.push_back(row);
	return result;
}

string InverseBWT(const string& bwt) {
	char nextChar = bwt[0];
	string text = bwt;
	text[text.size()-1] = '$';
	text[text.size()-2] = nextChar;
	// cout << "Text is: " << text << endl;
	vector<vector<int>> fmIndex = createFMIndex(bwt);

	// for (int i = 0; i < fmIndex.size(); ++i) {
	// 	for (int j = 0; j < fmIndex[i].size(); ++j) {
	// 		cout << fmIndex[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;

	vector<int> tracker = fmIndex[fmIndex.size()-1];
	int c = idx(nextChar);
	int pred = tracker[c] + fmIndex[0][c];
	int count = text.size() - 3;
	while (pred != 0) {
		nextChar = bwt[pred];
		c = idx(nextChar);
		pred = tracker[c] + fmIndex[pred][c];
		// if (nextChar != '$') {
		if (count >= 0) {
			text[count--] = nextChar;
		}
		
		// if (count >= -1)
		// 	cout << "Text is: " << text << endl;
	}

	return text;
}

int main() {
	string bwt;
	cin >> bwt;
	cout << InverseBWT(bwt) << endl;
	return 0;
}
