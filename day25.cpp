#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MOD = 20201227;
int cardPub, doorPub;

int power(int n, int p, int mod) {
	int r = 1;
	for (; p; p >>= 1) {
		if (p & 1)
			r = (1LL * r * n) % MOD;
		n = (1LL * n * n) % MOD;
	}
	return r;
}

int babyStepGiantStep(int h) {
	int m = sqrt(MOD);
	unordered_map<int, int> tbl;
	int e = 1;

	for (int i = 0; i < m; i++){
		tbl[e] = i;
		e = (1LL * e * 7) % MOD;
	}

	int factor = power(7, MOD - m - 1, MOD);
	e = h;

	for (int i = 0; i < m; i++) {
		if (auto it = tbl.find(e); it != tbl.end())
			return i*m + it->second;
		e = (1LL * e * factor) % MOD;
	}

	return -1;
}

int main() {
	freopen("day25.in", "r", stdin);

	scanf("%d %d", &cardPub, &doorPub);

	int cardLoop = babyStepGiantStep(cardPub);
	assert(cardLoop != -1);

	printf("%d\n", power(doorPub, cardLoop, MOD));
}

