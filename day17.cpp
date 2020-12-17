#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int INF = 0x3f3f3f3f;

typedef tuple<int, int, int, int> Point;

map<Point, char> m;

int dx[] = {1, 0, -1, 0, 1, 1, -1, -1, 0};
int dy[] = {0, 1, 0, -1, 1, -1, -1, 1, 0};
int dz[] = {1, 0, -1};
int dw[] = {1, 0, -1};

pair<int, int> xlim, ylim, zlim, wlim;

void updateLimits(int x, int y, int z, int w) {
	xlim = { min(xlim.first, x - 1), max(xlim.second, x + 1) };
	ylim = { min(ylim.first, y - 1), max(ylim.second, y + 1) };
	zlim = { min(zlim.first, z - 1), max(zlim.second, z + 1) };
	wlim = { min(wlim.first, w - 1), max(wlim.second, w + 1) };
}

void read() {
	// Reset
	m.clear();
	xlim = ylim = zlim = wlim = {INF, -INF};

	// Re-read file
	cin.clear();
	cin.seekg(0);

	string line;
	for (int x = 0; cin >> line; ++x) {
		for (int y = 0; y < (int)line.length(); ++y) {
			auto tpl = make_tuple(x, y, 0, 0);
			if (line[y] == '#') m[tpl] = '#';
			updateLimits(x, y, 0, 0);
		}
	}
}

int activeNeighbors(int x, int y, int z, int w) {
	int ans = 0;

	for (int i = 0; i < 3; i++) {
		int nw = w + dw[i];
		for (int j = 0; j < 3; j++) {
			int nz = z + dz[j];
			for (int d = 0; d < 9; d++) {
				int nx = x + dx[d], ny = y + dy[d];

				// I have to move on at least 1 dimension
				if (nx == x && ny == y && nz == z && nw == w) continue;

				auto tpl = make_tuple(nx, ny, nz, nw);
				if (m[tpl] == '#') ++ans;
			}
		}
	}

	return ans;
}

void update(queue<pair<Point, char>>& q) {
	int x, y, z, w;
	Point tpl;
	char c;

	while (!q.empty()) {
		tie(tpl, c) = q.front();
		tie(x, y, z, w) = tpl;
		q.pop();

		if (c == '#')
			m[tpl] = c;	
		else
			m.erase(tpl);

		updateLimits(x, y, z, w);
	}
}

void epoch1() {
	queue<pair<Point, char>> q;

	for (int x = xlim.first; x <= xlim.second; x++) {
		for (int y = ylim.first; y <= ylim.second; y++) {
			for (int z = zlim.first; z <= zlim.second; z++) {
				auto tpl = make_tuple(x, y, z, 0);
				int active = activeNeighbors(x, y, z, 0);

				if (m[tpl] == '#' && active != 2 && active != 3)
					q.push({tpl, '.'});
				else if (m[tpl] != '#' && active == 3)
					q.push({tpl, '#'});
			}
		}
	}

	update(q);
}

void epoch2() {
	queue<pair<Point, char>> q;

	for (int x = xlim.first; x <= xlim.second; x++) {
		for (int y = ylim.first; y <= ylim.second; y++) {
			for (int z = zlim.first; z <= zlim.second; z++) {
				for (int w = wlim.first; w <= wlim.second; w++) {
					auto tpl = make_tuple(x, y, z, w);
					int active = activeNeighbors(x, y, z, w);

					if (m[tpl] == '#' && active != 2 && active != 3)
						q.push({tpl, '.'});
					else if (m[tpl] != '#' && active == 3)
						q.push({tpl, '#'});
				}
			}
		}
	}

	update(q);
}

int countActive() {
	return count_if(m.begin(), m.end(),
	[](const pair<Point, char>& it) { return it.second == '#'; });
}

void part1() {
	read();

	for (int i = 1; i <= 6; i++)
		epoch1();

	cout << countActive() << endl;
}

void part2() {
	read();

	for (int i = 1; i <= 6; i++)
		epoch2();

	cout << countActive() << endl;
}

int main() {
	freopen("day17.in", "r", stdin);

	part1();
	part2();

	return 0;
}
