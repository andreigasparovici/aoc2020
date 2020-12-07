#include <bits/stdc++.h>
using namespace std;

vector<int> nums;
unordered_set<int> exists;

void part1() {
	for (auto n : nums) {
		if (exists.find(2020 - n) != exists.end()) {
			printf("%d\n", n * (2020 - n));
			return;
		}
	}
}

void part2() {
	for (size_t i = 0; i < nums.size() - 1; i++) {
		for (size_t j = i + 1; j < nums.size(); j++) {
			if (exists.find(2020 - nums[i] - nums[j]) != exists.end()) {
				printf("%d\n", nums[i] * nums[j] * (2020 - nums[i] - nums[j]));
				return;
			}
		}
	}
}

int main() {
	freopen("day1.in", "r", stdin);

	int n;
	while (!feof(stdin)) {
		scanf("%d", &n);
		nums.push_back(n);
		exists.insert(n);
	}

	part1();
	part2();

	return 0;
}
