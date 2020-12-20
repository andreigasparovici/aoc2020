#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAX_TILES = 200;
char line[20];

int numTiles;

struct Tile {
	int id;
	int n{10};
	char a[10][11];

	friend istream& operator>>(istream& in, Tile& t) {
		char line[20];

		in.getline(line, 20);
		sscanf(line, "Tile %d:", &t.id);

		int i = 0;
		in.getline(line, 20);
		while (*line) {
			strcpy(t.a[i++], line);	
			in.getline(line, 20);
		}
		
		return in;
	}

	friend ostream& operator<<(ostream& out, const Tile& t) {
		out << "Tile " << t.id << ":\n";
		for (int i = 0; i < t.n - 1; i++) {
			out << t.a[i] << '\n';
		}
		out << t.a[t.n - 1];
		return out;
	}

	void flip() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n / 2; j++)
				swap(a[i][j], a[i][n - j - 1]);
	}

	void rotateLeft() {
		for (int i = 0; i < n / 2; i++) {
			for (int j = i; j < n - i - 1; j++) {
				int tmp = a[i][j];
				a[i][j] = a[j][n - i - 1];
				a[j][n - i - 1] = a[n - i - 1][n - j - 1];
				a[n - i - 1][n - j - 1] = a[n - j - 1][i];
				a[n - 1 - j][i] = tmp;
			}
		}
	}

	bool matchLeft(const Tile& left) {
		for (int i = 0; i < n; i++) {
			if (left.a[i][n - 1] != a[i][0])
				return false;
		}
		return true;
	}

	bool matchUp(const Tile& up) {
		for (int j = 0; j < n; j++) {
			if (up.a[n - 1][j] != a[0][j])
				return false;
		}
		return true;
	}
}tiles[MAX_TILES];

bitset<MAX_TILES> used;

const int MAX_SIDE = 12;
Tile sol[MAX_SIDE][MAX_SIDE];
int n;

bool found;

void bkt(int i, int j) {
	if (i == n) {
		found = true;
		return;
	}

	if (j == n) {
		bkt(i + 1, 0);
		return;
	}

	for (int k = 0; k < numTiles; k++) {
		if (used[k]) continue;

		sol[i][j] = tiles[k];

		// Try normal
		if ((i == 0 || sol[i][j].matchUp(sol[i - 1][j])) && (j == 0 || sol[i][j].matchLeft(sol[i][j - 1]))) {
			used[k] = true;
			bkt(i, j + 1);
			used[k] = false;
			if (found) return;
		}

		// Try flipped
		sol[i][j].flip();

		if ((i == 0 || sol[i][j].matchUp(sol[i - 1][j])) && (j == 0 || sol[i][j].matchLeft(sol[i][j - 1]))) {
			used[k] = true;
			bkt(i, j + 1);
			used[k] = false;
			if (found) return;
		}

		// Flip back
		sol[i][j].flip();

		// Try rotated
		for (int r = 1; r < 4; r++) {
			// Just rotated
			sol[i][j].rotateLeft();	

			if ((i == 0 || sol[i][j].matchUp(sol[i - 1][j])) && (j == 0 || sol[i][j].matchLeft(sol[i][j - 1]))) {
				used[k] = true;
				bkt(i, j + 1);
				used[k] = false;
				if (found) return;
			}

			// Rotated and flipped
			sol[i][j].flip();

			if ((i == 0 || sol[i][j].matchUp(sol[i - 1][j])) && (j == 0 || sol[i][j].matchLeft(sol[i][j - 1]))) {
				used[k] = true;
				bkt(i, j + 1);
				used[k] = false;
				if (found) return;
			}

			// Flip back
			sol[i][j].flip();
		}
	}
}

void read() {
	Tile tmp;

	while (cin >> tmp) {
		tiles[numTiles++] = tmp;
	}
}

int main() {
	freopen("day20.in", "r", stdin);

	read();

	n = sqrt(numTiles);
	assert(MAX_SIDE >= n);

	found = false;
	bkt(0, 0);

	assert(found);
	cout << 1LL * sol[0][0].id * sol[0][n - 1].id * sol[n - 1][0].id * sol[n - 1][n - 1].id << endl;
}

