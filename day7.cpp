#include <bits/stdc++.h>
using namespace std;

char line[100000];
const char* sep = " ,.\n";

unordered_map<string, vector<pair<string, int>>> graph;

void parseLine() {
	string node;

	char *p = strtok(line, sep);
	node.append(p);
	p = strtok(NULL, sep);
	node.append(" ");
	node.append(p);

	p = strtok(NULL, sep); // "bags"
	p = strtok(NULL, sep); // "contain"

	while (p) {
		pair<string, int> next;

		p = strtok(NULL, sep); // number / "no"

		if (!p) break;

		if (strcmp(p, "no") == 0)
			break;

		sscanf(p, "%d", &next.second);

		p = strtok(NULL, sep);
		next.first.append(p);
		p = strtok(NULL, sep);
		next.first.append(" ");
		next.first.append(p);

		graph[node].push_back(next);

		p = strtok(NULL, sep); // "bags"
	}
}

void read() {
	while (!feof(stdin)) {
		fgets(line, 100000, stdin);
		if (*line != '\n') parseLine();
	}
}

void dfs1(const string& node, unordered_map<string, bool>& used, bool& ok) {
	used[node] = true;

	if (node == "shiny gold") {
		ok = true;
		return;
	}

	for (auto next: graph[node]) {
		if (!used[next.first])
			dfs1(next.first, used, ok);
		if (ok) return;
	}
}

void part1() {
	unordered_map<string, bool> used;
	int ans = 0;

	for (auto node: graph) {
		if (node.first == "shiny gold") continue;

		bool ok = false;
		used.clear();

		dfs1(node.first, used, ok);

		if (ok) ++ans;
	}

	printf("%d\n", ans);
}

void dfs2(const string& node, unordered_map<string, bool>& used, unordered_map<string, int>& count, int coef=1) {
	used[node] = true;
	
	for (auto next: graph[node]) {
		count[node] += coef * next.second;
		dfs2(next.first, used, count, coef * next.second);
	}
}

void part2() {
	unordered_map<string, bool> used;
	unordered_map<string, int> count;

	dfs2("shiny gold", used, count);

	int ans = 0;
	for_each(count.begin(), count.end(), [&ans](const pair<string, int>& it) { ans += it.second; });

	printf("%d\n", ans);
}

int main() {
	freopen("day7.in", "r", stdin);

	read();

	part1();
	part2();

	return 0;
}
