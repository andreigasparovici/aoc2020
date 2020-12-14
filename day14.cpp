#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct Mask {
	char bits[36]{};

	LL apply(LL value) {
		bitset<36> b(value);
		for (int i = 35; i >= 0; i--)
			if (bits[35 - i] != 'X')
				b[i] = bits[35 - i] - '0';
		return b.to_ullong();
	}

	void bkt(int k, bitset<36>& sol, vector<LL>& result) {
		if (k == 36) {
			result.push_back(sol.to_ullong());
			return;
		}

		if (bits[k] != 'X') {
			if (bits[k] - '0' == 1)
				sol[35 - k] = bits[k] - '0';
			bkt(k + 1, sol, result);
		} else {
			sol[35 - k] = 0;
			bkt(k + 1, sol, result);
			sol[35 - k] = 1;
			bkt(k + 1, sol, result);
		}
	}

	vector<LL> applyFloating(LL index) {
		bitset<36> sol(index);
		vector<LL> result;
		bkt(0, sol, result);
		return result;
	}
}mask;

void part1() {
	fseek(stdin, 0, SEEK_SET);

	map<LL, LL> mem;

	char line[1000];
	while (fgets(line, 1000, stdin)) {
		if (line[1] == 'a') {
			char *maskBits = strchr(line, '=') + 2;
			strncpy(mask.bits, maskBits, 36);
		} else {
			LL index, value;
			sscanf(line, "mem[%lld] = %lld\n", &index, &value);

			mem[index] = mask.apply(value);
		}
	}

	LL ans = accumulate(mem.begin(), mem.end(), 0LL,
		[](const LL sum, const auto& it) { return sum + it.second; });

	printf("%lld\n", ans);
}

void part2() {
	fseek(stdin, 0, SEEK_SET);

	map<LL, LL> mem;

	char line[1000];
	while (fgets(line, 1000, stdin)) {
		if (line[1] == 'a') {
			char *maskBits = strchr(line, '=') + 2;
			strncpy(mask.bits, maskBits, 36);
		} else {
			LL index, value;
			sscanf(line, "mem[%lld] = %lld\n", &index, &value);

			auto indices = mask.applyFloating(index);
			for_each(indices.begin(), indices.end(), [&mem,value](LL i){ mem[i] = value; }); 
		}
	}

	LL ans = accumulate(mem.begin(), mem.end(), 0LL,
		[](const LL sum, const auto& it) { return sum + it.second; });

	printf("%lld\n", ans);
}

int main() {
	freopen("day14.in", "r", stdin);

	part1();
	part2();

	return 0;
}
