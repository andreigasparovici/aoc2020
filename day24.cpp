#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const char* d[] = {"e", "se", "sw", "w", "nw", "ne"};

int dx[] = {1, 0, -1, -1,  0,  1};
int dy[] = {0, 1,  1,  0, -1, -1};

const int BUFF_SIZE = 10000;
char buff[BUFF_SIZE];

int main() {
	freopen("day24.in", "r", stdin);

	map<pair<int, int>, int> mp;

	while (cin.getline(buff, BUFF_SIZE)) {
		int x = 0, y = 0;

		for (char *p = buff; *p;) {
			for (int i = 0; i < 6; i++) {
				if (strstr(p, d[i]) == p) {
					x += dx[i];
					y += dy[i];
					p += strlen(d[i]);
					continue;
				}
			}
		}

		mp[{x,y}] = !mp[{x, y}];
	}

	cout << count_if(mp.begin(), mp.end(), [](const auto& it){ return it.second == 1; });
}

