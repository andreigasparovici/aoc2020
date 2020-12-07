#include <bits/stdc++.h>
using namespace std;

pair<int, int> seatLocation(const string& seatCode) {
	pair<int, int> ans;

	int left = 0, right = 127;

	for (int i = 0; i < 7; i++) {
		int middle = (left + right) / 2;
		if (seatCode[i] == 'F')
			right = middle - 1;
		else
			left = middle + 1;
	}

	ans.first = left;

	left = 0, right = 7;

	for (int i = 0; i < 3; i++) {
		int middle = (left + right) / 2;
		if (seatCode[7 + i] == 'L')
			right = middle - 1;
		else
			left = middle + 1;
	}

	ans.second = left;

	return ans;
}

int seatId(const pair<int, int>& loc) {
	return loc.first * 8 + loc.second;
}

void part1(const vector<int>& seatIds) {
	cout << *max_element(seatIds.begin(), seatIds.end()) << endl;
}

void part2(const vector<int>& seatIds) {
	unordered_set<int> exists;

	for (auto id: seatIds)
		exists.insert(id);

	for (auto id: seatIds) {
		if (exists.find(id - 2) != exists.end() && exists.find(id - 1) == exists.end()) {
			cout << id - 1 << endl;
			return;
		}
	}
}

int main() {
	freopen("day5.in", "r", stdin);

	string line;
	vector<int> seatIds;

	while (cin >> line)
		seatIds.push_back(seatId(seatLocation(line)));

	part1(seatIds);
	part2(seatIds);

	return 0;
}
