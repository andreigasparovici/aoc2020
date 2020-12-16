#include <bits/stdc++.h>
using namespace std;
using LL=long long;

const int LINE = 10000;
char line[LINE];

struct Field {
	char field[30];
	pair<int, int> i1, i2;

	bool check(int val) { return (i1.first <= val && val <= i1.second) || (i2.first <= val && val <= i2.second); }

	bool checkAll(const vector<int>& vals) {
		return all_of(vals.begin(), vals.end(), [this](auto v) { return check(v); });
	}
};

vector<Field> fields;
vector<int> myTicket;
vector<vector<int>> nearby;

void read() {
	// Read fields
	fgets(line, LINE, stdin);

	for (Field f; *line && *line != '\n';) {
		char *p = strtok(line, ":");
		strcpy(f.field, p);

		p = strtok(NULL, " ");

		sscanf(p, "%d-%d", &f.i1.first, &f.i1.second);

		p = strtok(NULL, " \n");
		p = strtok(NULL, " \n");

		sscanf(p, "%d-%d", &f.i2.first, &f.i2.second);

		fields.push_back(f);

		fgets(line, LINE, stdin);
	}

	fgets(line, LINE, stdin);
	fgets(line, LINE, stdin);

	// Read my ticket
	for(char *p = strtok(line, ",\n"); p; p = strtok(NULL, ",\n")) {
		int val;
		sscanf(p, "%d", &val);
		myTicket.push_back(val);
	}

	// Read nearby tickets
	fgets(line, LINE, stdin);
	fgets(line, LINE, stdin);

	while (fgets(line, LINE, stdin) && *line != '\n') {
		nearby.push_back({});

		for(char *p = strtok(line, ",\n"); p; p = strtok(NULL, ",\n")) {
			int val;
			sscanf(p, "%d", &val);
			nearby.back().push_back(val);
		}
	}
}

void part1() {
	LL ans = 0;
	for (auto& t: nearby) {
		for (auto& val: t) {
			if (none_of(fields.begin(), fields.end(), [val](auto& f) { return f.check(val); }))
				ans += val;
		}
	}
	printf("%lld\n", ans);
}

vector<int> select(int i) {
	vector<int> ans;
	for (auto t: nearby)
		ans.push_back(t[i]);
	return ans;
}

void part2() {
	// Remove invalid tickets

	queue<int> q;
	for (int i = nearby.size() - 1; i >= 0; --i) {
		bool invalid = false;

		for (auto& val: nearby[i]) {
			if (none_of(fields.begin(), fields.end(), [val](auto& f) { return f.check(val); }))
				invalid = true;
		}

		if (invalid) q.push(i);
	}

	while (!q.empty()) {
		int i = q.front();
		nearby.erase(nearby.begin() + i);
		q.pop();
	}

	nearby.push_back(myTicket);

	vector<vector<int>> options;
	for (int i = 0; i < (int)fields.size(); i++) {
		auto values = select(i);
		options.push_back({});

		// Which fields validate all values?

		for (int j = 0; j < (int) fields.size(); j++) {
			if (fields[j].checkAll(values)) {
				options.back().push_back(j);
			}
		}
	}

	// Take the fields with least options first
	// Build greedy solution
	auto cmp = [options](int i, int j) { return options[i].size() > options[j].size(); };
	priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

	for (int i = 0; i < (int)fields.size(); i++)
		pq.push(i);

	vector<bool> used(fields.size(), false);
	vector<int> field(fields.size());

	while (!pq.empty()) {
		int i = pq.top();
		pq.pop();

		bool found = false;
		for (auto opt: options[i]) {
			if (!used[opt]) {
				field[i] = opt;
				used[opt] = true;
				found = true;
				break;
			}
		}

		assert(found);
	}

	LL ans = 1;

	for (int i = 0; i < (int)field.size(); ++i) {
		char *p = fields[field[i]].field;
		if (strstr(p, "departure") == p)
			ans *= myTicket[i];
	}

	printf("%lld\n", ans);
}

int main() {
	freopen("day16.in", "r", stdin);

	read();

	part1();
	part2();

	return 0;
}
