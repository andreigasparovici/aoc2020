#include <bits/stdc++.h>
using namespace std;

char line[1000];

void part1() {
	int ans = 0;

	while (!feof(stdin)) {
		fgets(line, 1000, stdin);

		unordered_set<char> answers;

		for (; *line != '\n'; fgets(line, 1000, stdin))
			for (char *p = line; *p && *p != '\n'; p++)
				answers.insert(*p);

		ans += answers.size();
	}

	printf("%d\n", ans);
}

void part2() {
	fseek(stdin, 0, SEEK_SET);
	
	int ans = 0;

	while (!feof(stdin)) {
		unordered_map<char, int> answers;

		int people;

		fgets(line, 1000, stdin);

		for (people = 0; *line != '\n'; ++people) {
			for (char *p = line; *p && *p != '\n'; p++)
				++answers[*p];

			fgets(line, 1000, stdin);
		}

		ans += count_if(answers.begin(), answers.end(), [&](pair<char, int> it) { return it.second == people; });
	}

	printf("%d\n", ans);
}

int main() {
	freopen("day6.in", "r", stdin);

	part1();
	part2();

	return 0;
}
