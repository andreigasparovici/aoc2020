#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int earliestTimestamp;
vector<int> buses;

void read() {
	fseek(stdin, 0, SEEK_SET);

	scanf("%d\n", &earliestTimestamp);

	char line[200];
	fgets(line, 200, stdin);
	char *p = strtok(line, ",\n");

	buses.clear();

	for (;p; p = strtok(NULL, ",\n")) {
		int b;

		if (*p == 'x') b = -1;
		else sscanf(p, "%d", &b);

		buses.push_back(b);
	}
}

void part1() {
	read();

	int minDeparture = INT_MAX, wait;

	for (auto& b: buses) {
		if (b == -1) continue;

		int departure = b * ceil(1. * earliestTimestamp / b);
		if (departure < minDeparture) {
			minDeparture = departure;
			wait = b * (departure - earliestTimestamp);
		}
	}

	printf("%d\n", wait);
}

void extendedEuclid(LL a, LL b, LL& d , LL& x, LL & y) {
	if (!b) {
		d = a;
		x = 1;
		y = 0;
		return;
	}
	
	LL xp, yp;
	extendedEuclid(b, a % b, d, xp, yp);
	x = yp;
	y = xp - (a / b) * yp;
}

LL inverseEuclid(LL n, LL m) {
	LL d, x, y;
	extendedEuclid(n, m, d, x, y);	
	while (x < m) x += m;
	return x;
}

pair<LL, LL> chineseRemainderTheorem(vector<LL>&a, vector<LL>& n) {
	LL M = accumulate(n.begin(), n.end(), 1LL, multiplies<>());

	LL Y = 0;
	for (int i = 0; i < (int)n.size(); i++) {
		LL m = M / n[i];
		Y = (Y + a[i] * m * inverseEuclid(m, n[i])) % M;
	}

	return {Y, M};
}

void part2() {
	read();

	vector<LL> a, n;

	for (auto it = buses.begin() + 1; it != buses.end(); ++it) {
		if (*it == -1) continue;
		a.push_back(buses.begin() - it);
		n.push_back(*it);
	}

	LL rem, mod, kmod;
	tie(rem, mod) = chineseRemainderTheorem(a, n);

	for (kmod = 0; (kmod + rem) % buses[0]; kmod += mod);

	printf("%lld\n", kmod + rem);
}

int main() {
	freopen("day13.in", "r", stdin);

	part1();
	part2();

	return 0;
}
