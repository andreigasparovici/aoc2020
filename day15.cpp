#include <bits/stdc++.h>
using namespace std;

vector<int> turns;

void read() {
	fseek(stdin, 0, SEEK_SET);
	turns.clear();

	int num;
	while (scanf("%d,", &num) == 1) {
		turns.push_back(num);
	}
}

int generateTurns(vector<int>& init, int turns) {
	int currentTurn = 0;
	multimap<int, int> turn;

	int lastSpoken;

	for (auto num: init) {
		turn.insert({num, ++currentTurn});
		lastSpoken = num;
	}

	for (++currentTurn; currentTurn <= turns; ++currentTurn) {
		if (currentTurn % 100000 == 0) {
			printf("\r%4.2f%%", 1. * currentTurn / turns * 100);
			fflush(stdout);
		}

		int nextSpoken;

		int count = turn.count(lastSpoken);
		auto range = turn.equal_range(lastSpoken);

		if (count > 2) {
			turn.erase(range.first, prev(range.second, 3));
			count = 2;
		}

		// If first time
		if (count == 1) {
			nextSpoken = 0;
		} else {
			// Not first time => get last turn
			int lastTurn = prev(range.second)->second;
			int secondLastTurn = prev(range.second, 2)->second;
			nextSpoken = lastTurn - secondLastTurn;
		}

		turn.insert({nextSpoken, currentTurn});
		lastSpoken = nextSpoken;
	}

	printf("\r%20c\r", ' ');

	return lastSpoken;
}

void part1() {
	read();

	printf("%d\n", generateTurns(turns, 2020));
}

void part2() {
	read();

	printf("%d\n", generateTurns(turns, 30000000));
}

int main() {
	freopen("day15.in", "r", stdin);

	//part1();
	part2();


	return 0;
}
