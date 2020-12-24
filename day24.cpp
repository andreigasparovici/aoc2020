#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const char* d[] = {"e", "se", "sw", "w", "nw", "ne"};

int dx[] = {1, 0, -1, -1,  0,  1};
int dy[] = {0, 1,  1,  0, -1, -1};

const int BUFF_SIZE = 10000;
char buff[BUFF_SIZE];

map<pair<int, int>, int> mp;
pair<int, int> xlim, ylim;

int countBlackTiles() {
	int ans = 0;

	for (int x = xlim.first; x <= xlim.second; x++)
		for (int y = ylim.first; y <= ylim.second; y++)
			if (mp[{x, y}]) ++ans;

	return ans;
}

void part1() {
	xlim = ylim = {0, 0};

	while (cin.getline(buff, BUFF_SIZE)) {
		int x = 0, y = 0;

		for (char *p = buff; *p;) {
			for (int i = 0; i < 6; i++) {
				if (strstr(p, d[i]) == p) {
					x += dx[i];
					y += dy[i];
					p += strlen(d[i]);
					continue;
				}
			}
		}

		xlim = {min(xlim.first, x), max(xlim.second, x)};
		ylim = {min(ylim.first, y), max(ylim.second, y)};

		mp[{x,y}] = !mp[{x, y}];
	}

	cout << countBlackTiles() << endl;
}

int countBlackNeighbors(int x, int y) {
	int ans = 0;
	for (int i = 0; i < 6; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (mp[{nx, ny}]) ++ans;
	}
	return ans;
}

void epoch() {
	queue<tuple<int, int, int>> updates;

	for (int x = xlim.first - 1; x <= xlim.second + 1; x++) {
		for (int y = ylim.first - 1; y <= ylim.second + 1; y++) {
			int n = countBlackNeighbors(x, y);
			if (mp[{x, y}] && (n == 0 || n > 2))
				updates.emplace(x, y, 0);
			else if (!mp[{x, y}] && n == 2)
				updates.emplace(x, y, 1);
		}
	}

	while (!updates.empty()) {
		auto [x, y, val] = updates.front();
		updates.pop();
		mp[{x, y}] = val;

		xlim = {min(xlim.first, x), max(xlim.second, x)};
		ylim = {min(ylim.first, y), max(ylim.second, y)};
	}
}

void part2() {
	for (int i = 1; i <= 100; i++)
		epoch();

	cout << countBlackTiles() << endl;
}

int main() {
	freopen("day24.in", "r", stdin);

	part1();
	part2();
}

