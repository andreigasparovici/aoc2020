#include <bits/stdc++.h>
using namespace std;

using LL = long long;

vector<int> A;
bitset<1000> inA;
int device;

void read() {
	int joltage;

	A.push_back(0);
	inA[0] = true;

	while (scanf("%d", &joltage) == 1) {
		A.push_back(joltage);
		inA[joltage] = true;
	}

	device = 3 + *max_element(A.begin(), A.end());
	A.push_back(device);
	inA[device] = true;
}

int sol[150];
bool used[150];
bool found;

void bkt1(int k) {
	if (k == (int)A.size()) {
		found = true;

		int diff1{}, diff3{};

		for (int i = 1; i < k; i++)
			if (sol[i] - sol[i - 1] == 1) ++diff1;
			else if (sol[i] - sol[i - 1] == 3) ++diff3;

		printf("%d\n", diff1 * diff3);
		return;	
	}

	if (found) return;

	for (int i = 0; i <= 3; i++) {
		int joltage = sol[k - 1] + i;

		if (joltage < 0 || !inA[joltage] || used[joltage])
			continue;

		sol[k] = joltage;
		used[joltage] = true;
		bkt1(k + 1);
		used[joltage] = false;
	}
}

void part1() {
	sol[0] = 0;
	used[0] = true;
	bkt1(1);
}

LL dp[200][200];

void part2() {
	dp[1][0] = 1;

	sort(A.begin(), A.end());

	for (int i = 2; i < (int)A.size(); i++) {
		for (int j = 0; j < (int)A.size(); j++) {
			dp[i][A[j]] = 0;

			for (int k = 1; k <= 3; k++)
				if (A[j] - k >= 0 && inA[A[j] - k])
					dp[i][A[j]] += dp[i - 1][A[j] - k];
		}
	}

	LL ans = 0;

	for (int i = 0; i < (int)A.size(); i++)
		ans += dp[i][device];

	printf("%lld\n", ans + 1);
}

int main() {
	freopen("day10.in", "r", stdin);

	read();

	part1();
	part2();

	return 0;
}
