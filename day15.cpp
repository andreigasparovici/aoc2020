#include <bits/stdc++.h>
using namespace std;

vector<int> turns;

void read() {
	fseek(stdin, 0, SEEK_SET);
	turns.clear();

	int num;
	while (scanf("%d,", &num) == 1)
		turns.push_back(num);
}

int nthTurn(vector<int>& init, int n) {
	// Bound based on the growth of The Van Eck Sequence (almost linear)
	static list<int> turn[30000000]{};
	for (int i = 0; i < 30000000; i++)
		turn[i].clear();

	int i = 0;

	int lastSpoken;

	for (auto num: init) {
		turn[num].push_back(++i);
		lastSpoken = num;
	}

	for (++i; i <= n; ++i) {
		int nextSpoken;

		auto& indices = turn[lastSpoken];
		if (indices.size() > 2)
			indices.pop_front();

		if (indices.size() == 1) {
			nextSpoken = 0;
		} else {
			auto last = prev(indices.end());
			nextSpoken = *last - *prev(last);
		}

		turn[nextSpoken].push_back(i);
		lastSpoken = nextSpoken;
	}

	return lastSpoken;
}

void part1() {
	read();

	printf("%d\n", nthTurn(turns, 2020));
	fflush(stdout);
}

void part2() {
	read();

	printf("%d\n", nthTurn(turns, 30000000));
	fflush(stdout);
}

int main() {
	freopen("day15.in", "r", stdin);

	part1();
	part2();

	return 0;
}
