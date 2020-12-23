#include <bits/stdc++.h>
using namespace std;

const int NMAX = 1000000;

int P[NMAX + 1], N[NMAX + 1], H;

void push_back(int x) {
	if (H == -1) {
		H = x;
		P[x] = N[x] = x;
		return;
	}
	
	if (H == N[H]) {
		N[x] = H;
		P[x] = H;
		N[H] = x;
		P[H] = x;
		return;
	}

	int L = P[H];
	N[x] = H;
	P[x] = L;
	N[L] = x;
	P[H] = x;
}

void delete_n(int node, int count) {
	while (count--) {
		int aux = N[node];
		N[P[node]] = N[node];
		P[N[node]] = P[node];
		node = aux;
	}
}

void insert_after(int node, const vector<int>& v) {
	for (auto val: v) {
		N[val] = N[node];
		P[val] = node;
		P[N[node]] = val;
		N[node] = val;
		node = val;
	}
}

void epoch(int S, int max_val) {
	vector<int> picked{N[S], N[N[S]], N[N[N[S]]]};

	delete_n(N[S], 3);
	H = S;

	int dest = S;
	do {
		dest--;
		if (!dest) dest = max_val;
	} while(find(picked.begin(), picked.end(), dest) != picked.end());

	insert_after(dest, picked);
}

//vector<int> state{3, 8, 9, 1, 2, 5, 4, 6, 7};
vector<int> state{3, 6, 8, 1, 9, 5, 7, 4, 2};

void part1() {
	H = -1;

	for_each(state.begin(), state.end(), push_back);

	int c = state[0];

    for (int i = 1; i <= 100; i++) {
		epoch(c, 9);
        c = N[c];
    }

	int s = 1;

	for (int n = N[s]; n != s; n = N[n])
		cout << n;
	cout << endl;
}

void part2() {
	fill(N, N + NMAX + 1, 0);
	fill(P, P + NMAX + 1, 0);
	H = -1;

	for_each(state.begin(), state.end(), push_back);

	for (int i = 10; i <= NMAX; i++)
		push_back(i);

	int c = state[0];

    for (int i = 1; i <= 10 * NMAX; i++) {
		epoch(c, NMAX);
        c = N[c];
    }

	cout << 1LL * N[1] * N[N[1]] << endl;
}

int main() {
	part1();
	part2();
}
