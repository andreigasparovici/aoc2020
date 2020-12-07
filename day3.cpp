#include <bits/stdc++.h>
using namespace std;

int n, len;
char a[400][400];

void read() {
	while(!feof(stdin))
		scanf("%s\n", a[n++]);
	len = strlen(a[0]);
}

int count_trees(int right, int down) {
	int ans = 0;
	for (int i = 0, j = 0; i < n; i += down, j += right)
		if (a[i][j % len] == '#')
			++ans;
	return ans;
}

int main() {
	freopen("day3.in", "r", stdin);

	read();

	printf("%d\n", count_trees(3, 1));

	long long ans = 1;
	ans *= count_trees(1, 1);
	ans *= count_trees(3, 1);
	ans *= count_trees(5, 1);
	ans *= count_trees(7, 1);
	ans *= count_trees(1, 2);
	printf("%lld\n", ans);
}
