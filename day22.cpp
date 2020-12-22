#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
	freopen("day22.in", "r", stdin);

	list<int> p1, p2;

	char line[100];
	cin.getline(line, 100); // Skip "Player 1"
	cin.getline(line, 100);

	while (*line) {
		p1.emplace_back();
		sscanf(line, "%d", &p1.back());
		cin.getline(line, 100);
	}

	cin.getline(line, 100); // Skip "Player 2"
	cin.getline(line, 100);

	while (!cin.eof()) {
		p2.emplace_back();
		sscanf(line, "%d", &p2.back());
		cin.getline(line, 100);
	}

	while (!p1.empty() && !p2.empty()) {
		int top1 = p1.front(), top2 = p2.front();
		p1.pop_front();
		p2.pop_front();


		if (top1 > top2) {
			p1.push_back(top1);
			p1.push_back(top2);
		} else {
			p2.push_back(top2);
			p2.push_back(top1);
		}
	}

	const list<int>& winner = !p1.empty() ? p1 : p2;

	int score = 0, i = 0;
	for (auto it = winner.rbegin(); it != winner.rend(); it++)
		score += (++i) * (*it);

	cout << score << endl;
}

