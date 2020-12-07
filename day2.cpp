#include <bits/stdc++.h>
using namespace std;

struct Line {
	int min, max;
	char c;
	char s[50];

	bool isValid1() {
		int count = 0;
		for (char *p = s; *p; p++)
			if (*p == c)
				++count;
		return min <= count && count <= max;
	}

	bool isValid2() {
		return (s[min - 1] == c) ^ (s[max - 1] == c);
	}
};

int main() {
	freopen("day2.in", "r", stdin);

	Line line;
	vector<Line> input;

	while (!feof(stdin)) {
		scanf("%d-%d %c: %s\n", &line.min, &line.max, &line.c, line.s);
		input.push_back(line);
	}

	printf("%ld\n", count_if(input.begin(), input.end(), [](Line& line) { return line.isValid1(); }));

	printf("%ld\n", count_if(input.begin(), input.end(), [](Line& line) { return line.isValid2(); }));
}
