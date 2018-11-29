#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
	string result = "";
	vector<string> strings;
	string shortString = text;
	int l = text.size() - 1;
	strings.push_back(shortString);

	for (int i = 1; i < text.size(); ++i) {
		shortString = text.substr(i, text.size() - i) + text.substr(0, i);
		// cout << shortString << endl;
		strings.push_back(shortString);
	}

	// for (int i = 0; i < strings.size(); ++i) {
	// 	cout << strings[i] << endl;
	// }

	std::sort(strings.begin(), strings.end());

	// for (int i = 0; i < strings.size(); ++i) {
	// 	cout << strings[i] << endl;
	// }

	for (int i = 0; i < strings.size(); ++i) {
		result = result + strings[i][l];
	}

	return result;
}

int main() {
	string text;
	cin >> text;
	cout << BWT(text) << endl;
	return 0;
}