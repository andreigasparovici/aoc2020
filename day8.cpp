#include <bits/stdc++.h>
using namespace std;

struct Instruction {
	string operation;
	int argument;

	friend ostream& operator<<(ostream& out, Instruction& instruction) {
		out << instruction.operation;
		if (instruction.operation != "nop")
			out << " " << instruction.argument;
		return out;
	}

	friend istream& operator>>(istream& in, Instruction& instruction) {
		in >> instruction.operation >> instruction.argument;
		return in;
	}

	int next(int i) {
		if (operation == "nop") return i + 1;
		if (operation == "acc") return i + 1;
		if (operation == "jmp") return i + argument;
		return -1;
	}

	int accumulate(int acc) {
		if (operation == "acc") return acc + argument;
		return acc;
	}

	pair<int, int> eval(int accumulator, int index) {
		return {accumulate(accumulator), next(index)};
	}
};

vector<Instruction> instructions;

void read() {
	for (Instruction tmp; cin >> tmp;)
		instructions.push_back(tmp);
}

void part1() {
	int accumulator{};

	vector<bool> used(instructions.size(), false);

	int i = 0;
	int nextAccumulator, nextI;

	do {
		used[i] = true;

		tie(nextAccumulator, nextI) = instructions[i].eval(accumulator, i);
		i = nextI, accumulator = nextAccumulator;
	} while (!used[i]);

	cout << accumulator << endl;
}

void findCandidates(int node, vector<bool>& used, bool& foundCycle, vector<int>& candidates) {
	used[node] = true;

	int next = instructions[node].next(node);

	if (!used[next])
		findCandidates(next, used, foundCycle, candidates);
	else
		foundCycle = true;

	if (foundCycle) {
		string tmp = instructions[node].operation;
		if (tmp == "jmp" || tmp == "nop") {
			instructions[node].operation = (tmp == "jmp" ? "nop": "jmp");

			int newNext = instructions[node].next(node);
			if (!used[newNext])
				candidates.push_back(node);

			instructions[node].operation = tmp;
		}
	}
}

void eval(int node, vector<bool>& used, bool& foundCycle, int& accumulator) {
	if (foundCycle) return;

	int nextNode, nextAccumulator;
	tie(nextAccumulator, nextNode) = instructions[node].eval(accumulator, node);

	if (nextNode >= (int)instructions.size()) {
		accumulator = nextAccumulator;
		return;
	}

	used[node] = true;

	if (!used[nextNode]) {
		accumulator = nextAccumulator;
		eval(nextNode, used, foundCycle, accumulator);
	} else {
		foundCycle = true;
	}
}

void part2() {
	vector<bool> used(instructions.size(), false);
	bool foundCycle = false;

	vector<int> candidates;
	findCandidates(0, used, foundCycle, candidates);

	sort(candidates.begin(), candidates.end(), greater<int>());

	for (auto node: candidates) {
		string tmp = instructions[node].operation;
		instructions[node].operation = (tmp == "jmp" ? "nop": "jmp");

		fill(used.begin(), used.end(), false);

		foundCycle = false;
		int accumulator = 0;

		eval(0, used, foundCycle, accumulator);

		if (!foundCycle) {
			cout << accumulator << endl;
			return;
		}

		instructions[node].operation = tmp;
	}
}

int main() {
	freopen("day8.in", "r", stdin);

	read();

	part1();
	part2();

	return 0;
}
