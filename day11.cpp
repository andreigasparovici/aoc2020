#include <bits/stdc++.h>
using namespace std;

const int di[] = {0, 1, 0, -1, 1, 1, -1, -1};
const int dj[] = {1, 0, -1, 0, 1, -1, -1, 1};

const char FREE = 'L', OCCUPIED = '#', FLOOR = '.';

char seats[100][100];
int N, M;

int countOccupiedNeighbours(int i, int j) {
	int ans = 0;

	for (int d = 0; d < 8; d++) {
		int ni = i + di[d], nj = j + dj[d];

		if (ni < 0 || nj < 0 || ni >= N || nj >= M)
			continue;

		if (seats[ni][nj] == OCCUPIED)
			++ans;
	}

	return ans;
}

int countOccupiedVisible(int i, int j) {
	int ans = 0;

	for (int d = 0; d < 8; d++) {
		int ni = i + di[d], nj = j + dj[d];
		bool found = false;

		for (; !found ; ni += di[d], nj += dj[d]) {
			if (ni < 0 || nj < 0 || ni >= N || nj >= M)
				break;

			if (seats[ni][nj] == OCCUPIED)
				found = true;

			if (seats[ni][nj] == FREE)
				break;
		}

		ans += found;
	}

	return ans;
}

int countOccupied() {
	int ans = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (seats[i][j] == OCCUPIED)
				++ans;
	return ans;
}

void runUpdates(queue<tuple<int, int, char>>& updates) {
	int i, j;
	char c;

	while (!updates.empty()) {
		tie(i, j, c) = updates.front();
		updates.pop();
		seats[i][j] = c;
	}
}

bool epoch1() {
	queue<tuple<int, int, char>> updates;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (seats[i][j] == FLOOR) continue;

			int n = countOccupiedNeighbours(i, j);

			if (seats[i][j] == FREE && n == 0)
				updates.emplace(i, j, OCCUPIED);
			else if (seats[i][j] == OCCUPIED && n >= 4)
				updates.emplace(i, j, FREE);
		}
	}

	bool changed = !updates.empty();
	runUpdates(updates);

	return changed;
}

bool epoch2() {
	queue<tuple<int, int, char>> updates;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (seats[i][j] == FLOOR) continue;

			int n = countOccupiedVisible(i, j);

			if (seats[i][j] == FREE && n == 0)
				updates.emplace(i, j, OCCUPIED);
			else if (seats[i][j] == OCCUPIED && n >= 5)
				updates.emplace(i, j, FREE);
		}
	}

	bool changed = !updates.empty();
	runUpdates(updates);

	return changed;
}

void read() {
	fseek(stdin, 0, SEEK_SET);

	N = 0;
	while (scanf("%s", seats[N]) == 1) 
		++N;

	M = strlen(seats[0]);
}

int main() {
	freopen("day11.in", "r", stdin);

	for (read(); epoch1(););
	printf("%d\n", countOccupied());

	for (read(); epoch2(); );
	printf("%d\n", countOccupied());

	return 0;
}
