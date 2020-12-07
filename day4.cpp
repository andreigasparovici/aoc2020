#include <bits/stdc++.h>
using namespace std;

string keys[]{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};
const char* sep=": \n";

bool validateByr(const string&s) {
	if (s.length() != 4) return false;

	if (!all_of(s.begin(), s.end(), [](char c) { return isdigit(c); }))
		return false;

	return 1920 <= stoi(s) && stoi(s) <= 2002;
}

bool validateIyr(const string& s) {
	if (s.length() != 4) return false;

	if (!all_of(s.begin(), s.end(), [](char c) { return isdigit(c); }))
		return false;

	return 2010 <= stoi(s) && stoi(s) <= 2020;
}

bool validateEyr(const string& s) {
	if (s.length() != 4) return false;

	if (!all_of(s.begin(), s.end(), [](char c) { return isdigit(c); }))
		return false;

	return 2020 <= stoi(s) && stoi(s) <= 2030;
}

bool validateHgt(const string& s) {
	if (s.rfind("cm") == s.length() - 2) {
		int val = stoi(s.substr(0, s.length() - 2));
		return 150 <= val && val <= 193;
	} else if (s.rfind("in") == s.length() - 2) {
		int val = stoi(s.substr(0, s.length() - 2));
		return 59 <= val && val <= 76;
	} 

	return false;
}

bool validateHcl(const string& s) {
	if (s.length() != 7) return false;

	if (s[0] != '#') return false;

	return all_of(s.begin() + 1, s.end(), [](char c) { return isxdigit(c) && !isupper(c); });
}

bool validateEcl(const string& s) {
	string values[]{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

	return any_of(values, values + 7, [&](string& v) { return v == s; });
}

bool validatePid(const string& s) {
	if (s.length() != 9) return false;

	return all_of(s.begin(), s.end(), [](char c) { return isdigit(c); });
}

struct Passport{
	unordered_map<string, string> data;

	friend istream& operator>>(istream& in, Passport& passport) {
		passport.data.clear();

		char line[100000];

		do {
			in.getline(line, 100000);

			for (char *p = strtok(line, sep); p; p = strtok(NULL, sep)) {
				string key = p;
				p = strtok(NULL, sep);
				string value = p;
				passport.data[key] = value;
			}

		} while (*line);

		return in;
	}

	bool isValid1() {
		for (auto key: keys) {
			if (key == "cid") continue;
			if (data.find(key) == data.end())
				return false;
		}

		return true;
	}

	bool isValid2() {
		return validateByr(data["byr"]) && validateIyr(data["iyr"]) && \
				validateEyr(data["eyr"]) && validateHgt(data["hgt"]) && \
				validateHcl(data["hcl"]) && validateEcl(data["ecl"]) && \
				validatePid(data["pid"]);
	}
};

int main() {
	freopen("day4.in", "r", stdin);


	Passport p;	
	vector<Passport> passports;

	while (!cin.eof()) {
		cin >> p;
		passports.push_back(p);
	}

	printf("%ld\n", count_if(passports.begin(), passports.end(), [](Passport& p) { return p.isValid1(); }));

	printf("%ld\n", count_if(passports.begin(), passports.end(), [](Passport& p) { return p.isValid2(); }));

	return 0;
}
