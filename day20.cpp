#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAX_TILES = 200;
const int MAX_SIDE = 12;

const char* monster[]{
	{"                  # "},
	{"#    ##    ##    ###"},
	{" #  #  #  #  #  #   "},
};

class Matrix {
protected:
	vector<vector<char>> a;
	int n;

public:
	Matrix(int n) : n(n) {
		a.resize(n);
		for (int i = 0; i < n; i++)
			a[i].resize(n);
	}

	int size() { return n; }

	char& at(int i, int j) { return a[i][j]; }

	void flipHoriz() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n / 2; j++)
				swap(a[i][j], a[i][n - j - 1]);
	}

	void flipVert() {
		for (int j = 0; j < n; j++)
			for (int i = 0; i < n / 2; i++)
				swap(a[i][j], a[n - i - 1][j]);
	}

	void rotate() {
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

	int count(char c) {
		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				if (a[i][j] == c) ++ans;
		}
		return ans;
	}
};

struct Tile : public Matrix {
	int id;

	Tile() : Matrix(10) {}

	friend istream& operator>>(istream& in, Tile& t) {
		char line[20];

		in.getline(line, 20);
		sscanf(line, "Tile %d:", &t.id);

		int i = 0;
		in.getline(line, 20);
		while (*line) {
			for (int j = 0; line[j]; j++)
				t.at(i, j) = line[j];
			i++;
			in.getline(line, 20);
		}
		
		return in;
	}

	bool matchLeft(Tile& left) {
		for (int i = 0; i < n; i++) {
			if (left.at(i, n - 1) != at(i, 0))
				return false;
		}
		return true;
	}

	bool matchUp(Tile& up) {
		for (int j = 0; j < n; j++) {
			if (up.at(n - 1, j) != at(0, j))
				return false;
		}
		return true;
	}
};

vector<Tile> tiles;

bitset<MAX_TILES> used;
Tile sol[MAX_SIDE][MAX_SIDE];

void bkt(int i, int j, int n, bool& found) {
	if (i == n) {
		found = true;
		return;
	}

	if (j == n) {
		bkt(i + 1, 0, n, found);
		return;
	}

	for (int k = 0; k < (int)tiles.size(); k++) {
		if (used[k]) continue;

		sol[i][j] = tiles[k];

		// Try normal
		if ((i == 0 || sol[i][j].matchUp(sol[i - 1][j])) && (j == 0 || sol[i][j].matchLeft(sol[i][j - 1]))) {
			used[k] = true;
			bkt(i, j + 1, n, found);
			used[k] = false;
			if (found) return;
		}

		// Try flipped
		sol[i][j].flipHoriz();

		if ((i == 0 || sol[i][j].matchUp(sol[i - 1][j])) && (j == 0 || sol[i][j].matchLeft(sol[i][j - 1]))) {
			used[k] = true;
			bkt(i, j + 1, n, found);
			used[k] = false;
			if (found) return;
		}

		// Flip back
		sol[i][j].flipHoriz();

		// Try rotated
		for (int r = 1; r < 4; r++) {
			// Just rotated
			sol[i][j].rotate();	

			if ((i == 0 || sol[i][j].matchUp(sol[i - 1][j])) && (j == 0 || sol[i][j].matchLeft(sol[i][j - 1]))) {
				used[k] = true;
				bkt(i, j + 1, n, found);
				used[k] = false;
				if (found) return;
			}

			// Try flipped
			sol[i][j].flipHoriz();

			if ((i == 0 || sol[i][j].matchUp(sol[i - 1][j])) && (j == 0 || sol[i][j].matchLeft(sol[i][j - 1]))) {
				used[k] = true;
				bkt(i, j + 1, n, found);
				used[k] = false;
				if (found) return;
			}

			// Flip back
			sol[i][j].flipHoriz();
		}
	}
}

bool monsterStartsAt(Matrix& mat, int i, int j) {
	bool found = true;

	int len = strlen(monster[0]);

	for (int k = 0; k < 3 && found; k++) {
		for (int l = 0; l < len; l++) {
			if (monster[k][l] == '#' && mat.at(i + k, j + l) != monster[k][l])
				found = false;
		}
	}

	return found;
}

int countMonsters(Matrix& mat) {
	int len = strlen(monster[0]);

	int count = 0;
	for (int i = 0; i < mat.size() - 3; i++) {
		for (int j = 0; j < mat.size() - len; j++) {
			if (monsterStartsAt(mat, i, j))
				++count;
		}
	}

	return count;
}

int findMonsters(Matrix& mat) {
	int count;

	// Try as-is
	if ((count = countMonsters(mat)) != 0) return count;

	// Try flipped
	mat.flipHoriz();
	if ((count = countMonsters(mat)) != 0) return count;
	mat.flipHoriz();

	mat.flipVert();
	if ((count = countMonsters(mat)) != 0) return count;
	mat.flipVert();


	for (int k = 1; k < 4; k++) {
		// Try rotate
		mat.rotate();

		if ((count = countMonsters(mat)) != 0) return count;

		// Try rotate and flip
		mat.flipHoriz();
		if ((count = countMonsters(mat)) != 0) return count;
		mat.flipHoriz();

		mat.flipVert();
		if ((count = countMonsters(mat)) != 0) return count;
		mat.flipVert();
	}

	return -1;
}

int main() {
	freopen("day20.in", "r", stdin);

	// Read
	for (Tile tmp; cin >> tmp; tiles.push_back(tmp));

	int n = sqrt(tiles.size());
	assert(MAX_SIDE >= n);

	// Part 1
	bool found = false;
	bkt(0, 0, n, found);

	assert(found);

	LL part1Ans = 1LL * sol[0][0].id * sol[0][n - 1].id * sol[n - 1][0].id * sol[n - 1][n - 1].id;
	cout << part1Ans << endl;

	// Part 2
	Matrix bigMat(8 * n);
	int r = 0, c = 0;

	for (int i = 0; i < 10 * n; i++) {
		for (int j = 0; j < 10 * n; j++) {
			if ((i % 10) > 0 && (i % 10) < 9 && (j % 10) > 0 && (j % 10) < 9) {
				bigMat.at(r, c++) = sol[i / 10][j / 10].at(i % 10, j % 10);
				if (c == bigMat.size()) {
					r++;
					if (r < bigMat.size()) c = 0;
				}
			}
		}
	}


	int numMonsters = findMonsters(bigMat);

	int monsterSize = 0;
	int len = strlen(monster[0]);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < len; j++)
			if (monster[i][j] == '#') ++monsterSize;

	int part2Ans = bigMat.count('#') - numMonsters * monsterSize;
	cout << part2Ans << endl;
}
