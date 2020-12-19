#include <bits/stdc++.h>
using namespace std;

#define _GLIBCXX_REGEX_STATE_LIMIT 1000000

const int MAX_LINE = 100000;
const int MAX_RULES = 100000;

char line[MAX_LINE];

char character[MAX_RULES];
vector<vector<int>> graph[MAX_RULES];

bitset<MAX_RULES> used;
string memo[MAX_RULES];

vector<string> str;

string build(int i) {
    if (!memo[i].empty())
        return memo[i];

    string re;

    if (character[i] != '#') {
        re += character[i];
    } else {
        for (auto it = graph[i].begin(); it != graph[i].end(); ++it) {
            for (auto j : *it) {
				auto rej = build(j);
				if (rej.find('|') != string::npos)
					re += "(" + rej + ")";
				else
					re += rej;
			}

            if (next(it) != graph[i].end())
                re.append("|");
        }
    }

    memo[i] = re;
    return re;
}

void read() {
    fgets(line, MAX_LINE, stdin);

    memset(character, '#', sizeof(character));

    while (*line != '\n') {
        char *p = strtok(line, ":");

        int i = stoi(p);

        p = strtok(nullptr, " ");

        graph[i].emplace_back();

        for (; p; p = strtok(nullptr, " ")) {
            if (*p == '|') {
                graph[i].emplace_back();
            } else if (*p == '\"') {
                character[i] = p[1];
            } else {
                graph[i].back().push_back(stoi(p));
            }
        }

        fgets(line, MAX_LINE, stdin);
    }

	while (fgets(line, MAX_LINE, stdin) && *line != '\n') {
		char *p = strtok(line, "\n");
		str.push_back(p);
	}
}


void part1() {
	auto re = regex("^" + build(0) + "$");
	printf("%ld\n", count_if(str.begin(), str.end(), [re](const string& s) { return regex_match(s, re); }));
}

void part2() {
	fill(memo, memo + MAX_RULES, "");

	const int MAX_RECUR = 6;

	graph[8].clear();
	for (int k = 1; k <= MAX_RECUR; k++) {
		graph[8].emplace_back();
		for (int i = 1; i <= k; i++)
			graph[8].back().push_back(42);
	}

	graph[11].clear();
	for (int k = 1; k <= MAX_RECUR; k++) {
		graph[11].emplace_back();
		for (int i = 1; i <= k; i++)
			graph[11].back().push_back(42);
		for (int i = 1; i <= k; i++)
			graph[11].back().push_back(31);
	}

	auto re = regex("^" + build(0) + "$");
	printf("%ld\n", count_if(str.begin(), str.end(), [re](const string& s) { return regex_match(s, re); }));
}

int main() {
    freopen("day19.in", "r", stdin);

    read();

	part1();
	part2();
}
