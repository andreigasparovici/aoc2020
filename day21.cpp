#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef set<string> S;

const int MAX_BUFF = 100000;
static char buff[MAX_BUFF];

struct Line {
	S ingredients;
	list<string> allergens;

	friend istream& operator>>(istream& in, Line& line) {
		line.ingredients.clear();
		line.allergens.clear();

		in.getline(buff, MAX_BUFF);

		char *par = strchr(buff, '(');

		char *p = strtok(buff, " ");
		while (p < par) {
			line.ingredients.insert(p);
			p = strtok(NULL, " ");
		}


		p = strtok(NULL, ", )\n"); // Skip "contains"
		while (p) {
			line.allergens.push_back(p);
			p = strtok(NULL, ", )\n");
		}

		return in;
	}
};

void read(list<Line>& input) {
	for(Line line; cin >> line; input.push_back(line));
}

S operator&(const S& x, const S& y) {
	S aux;
	set_intersection(x.begin(), x.end(), y.begin(), y.end(), inserter(aux, aux.begin()));
	return aux;
}

S& operator&=(S& x, const S& y) { x = x & y; return x; }

S operator|(const S& x, const S& y) {
	S aux;
	set_union(x.begin(), x.end(), y.begin(), y.end(), inserter(aux, aux.begin()));
	return aux;
}

S& operator|=(S& x, const S& y) { x = x | y; return x; }

S operator-(const S& x, const S& y) {
	S aux;
	set_difference(x.begin(), x.end(), y.begin(), y.end(), inserter(aux, aux.begin()));
	return aux;
}

int main() {
	freopen("day21.in", "r", stdin);

	list<Line> input;
	read(input);

	unordered_map<string, S> mp;
	S ingredients;

	unordered_map<string, int> occ;

	for (auto line: input) {
		for (auto al: line.allergens) {
			if (mp.find(al) == mp.end())
				mp[al] = line.ingredients;
			else
				mp[al] &= line.ingredients;
		}

		for (auto in: line.ingredients)
			occ[in]++;

		ingredients |= line.ingredients;
	}

	S safe = ingredients - accumulate(mp.begin(), mp.end(), S(), [mp](const auto& x, const auto& y) { return x | y.second; });

	int ans1 = 0;
	for (auto s: safe) ans1 += occ[s];
	cout << ans1 << endl;

	map<string, string> unique_mp;

	while (any_of(mp.begin(), mp.end(), [](const auto& it) { return !it.second.empty(); })) {
		for (auto [k, v]: mp) {
			if (v.size() == 1) {
				unique_mp[k] = *v.begin();
				v.clear();
			}
		}

		for (auto& [k, ignore]: mp) {
			for (auto [ignore, v]: unique_mp)
				mp[k].erase(v);
		}
	}

	ostringstream out;
	for (auto& [ignore, v]: unique_mp)
		out << v << ',';

	auto ans2 = out.str();
	ans2.erase(prev(ans2.end()), ans2.end());
	cout << ans2;
}

