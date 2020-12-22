#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

typedef list<int> Player;

ostream& operator<<(ostream& out, const Player& p) {
	for (auto it = p.begin(); it != p.end(); ++it) {
		out << *it;
		if (next(it) != p.end())
			out << ' ';
	}
	return out;
}

istream& operator>>(istream& in, Player& p) {
	const int BUFFSIZE =100;
	static char buff[BUFFSIZE];

	cin.getline(buff, BUFFSIZE); // Skip "Player x"
	cin.getline(buff, BUFFSIZE);

	p.clear();

	while (*buff && !cin.eof()) {
		p.emplace_back();
		sscanf(buff, "%d", &p.back());
		cin.getline(buff, BUFFSIZE);
	}

	return in;
}

int score(const Player& p) {
	int ans = 0, i = 0;
	for (auto it = p.rbegin(); it != p.rend(); it++)
		ans += (++i) * (*it);
	return ans;
}

Player firstn(const Player& p, size_t n) {
	auto end = next(p.begin(), min(n, p.size()));
	return Player(p.begin(), end);
}

void part1(Player p1, Player p2) {
	while (!p1.empty() && !p2.empty()) {
		const auto [top1, top2] = make_pair(p1.front(),  p2.front());
		p1.pop_front();
		p2.pop_front();

		if (top1 > top2) {
			p1.push_back(top1);
			p1.push_back(top2);
		} else {
			p2.push_back(top2);
			p2.push_back(top1);
		}
	}

	const Player& winner = !p1.empty() ? p1 : p2;
	cout << score(winner) << endl;
}

pair<int, int> recursive(Player p1, Player p2) {
	set<pair<Player, Player>> states;
	
	for (int r = 1; !p1.empty() && !p2.empty(); r++) {
		if (states.find({p1, p2}) != states.end()) {
			return {1, score(p1)};
		}

		states.insert({p1, p2});

		auto [top1, top2] = make_pair(p1.front(),  p2.front());
		p1.pop_front();
		p2.pop_front();

		if ((int) p1.size() >= top1 && (int) p2.size() >= top2) {
			auto [winner, ignore] = recursive(firstn(p1, top1), firstn(p2, top2));
			if (winner == 1) {
				p1.push_back(top1);
				p1.push_back(top2);
			} else {
				p2.push_back(top2);
				p2.push_back(top1);
			}
		} else if (top1 > top2) {
			p1.push_back(top1);
			p1.push_back(top2);
		} else {
			p2.push_back(top2);
			p2.push_back(top1);
		}
	}

	if (!p1.empty())
		return {1, score(p1) };
	return {2, score(p2) };
}

void part2(Player p1, Player p2) {
	auto [ignore, score] = recursive(p1, p2);
	cout << score << endl;
}

int main() {
	freopen("day22.in", "r", stdin);

	Player p1, p2;
	cin >> p1 >> p2;

	part1(p1, p2);
	part2(p1, p2);
}
