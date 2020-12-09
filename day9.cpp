#include <bits/stdc++.h>
using namespace std;

using LL = long long;

const int PREAMBLE_SIZE = 25;

vector<LL> nums;

void read() {
	LL n;
	while (scanf("%lld", &n) == 1)
		nums.push_back(n);
}

LL part1() {
	for (int i = PREAMBLE_SIZE; i < (int)nums.size(); i++) {
		bool ok = false;		

		for (int j = i - PREAMBLE_SIZE; j < i; j++)
			for (int k = j + 1; k < i; k++)
				if (nums[j] + nums[k] == nums[i])
					ok = true;

		if (!ok)
			return nums[i];
	}

	return -1;
}

LL part2(LL n) {
	vector<LL> partial(nums.size());
	partial[0] = nums[0];

	for (int i = 1; i < (int)nums.size(); i++)
		partial[i] = nums[i] + partial[i - 1];

	bool found = false;
	pair<int, int> range;
	
	for (int i = 1; i < (int)nums.size() && !found; i++) {
		for (int j = i + 1; j < (int)nums.size() && !found; j++) {
			if (partial[j] - partial[i - 1] == n) {
				found = true;
				range = {i, j + 1};
			}
		}
	}

	LL min = *min_element(nums.begin() + range.first, nums.begin() + range.second);
	LL max = *max_element(nums.begin() + range.first, nums.begin() + range.second);

	return min + max;
}

int main() {
	freopen("day9.in", "r", stdin);

	read();

	LL ans1 = part1();
	printf("%lld\n", ans1);

	LL ans2 = part2(ans1);
	printf("%lld\n", ans2);

	return 0;
}
