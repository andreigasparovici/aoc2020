#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

char s[100000];

struct Node {
	Node *left{}, *right{};
	LL value{};
	char op{'#'};

	~Node() {
		delete left;
		delete right;
	}

	LL eval() {
		if (op == '#') return value;

		LL l = left->eval(), r = right->eval();
		return op == '+' ? l + r : l * r;
	}
};

Node* buildOps(int, int, const char*, int);

Node* build(int left, int right, int task) {
	if (task == 1) {
		// Addition and multiplication have the same precedence
		if (Node *node = buildOps(left, right, "+*", task))
			return node;
	} else if (task == 2) {
		// Addition before multiplication
		if (Node *node = buildOps(left, right, "*", task))
			return node;

		if (Node *node = buildOps(left, right, "+", task))
			return node;
	}
	
	if (s[left] == '(')
		return build(left + 1, right - 1, task);

	// Parse value (single digit)
	Node *node = new Node;
	node->value = s[left] - '0';
	return node;
}

Node* buildOps(int left, int right, const char* ops, int task) {
	int par = 0;
	
	for (int i = right; i >= left; i--) {
		if (s[i] == ')') ++par;
		else if (s[i] == '(') --par;
		else if (!par && strchr(ops, s[i])) {
			Node *node = new Node;
			node->op = s[i];
			node->left = build(left, i - 2, task);
			node->right = build(i + 2, right, task);
			return node;
		}
	}

	return nullptr;
}


void solve(int task) {
	fseek(stdin, 0, SEEK_SET);

	LL ans = 0;

	while (fgets(s, 100000, stdin)) {
		int len = strlen(s);
		if (s[len - 1] == '\n')
			len--;

		if (!len) continue;

		Node *root = build(0, len - 1, task);
		ans += root->eval();
		delete root;
	}

	printf("%lld\n", ans);
}

int main() {
	freopen("day18.in", "r", stdin);

	solve(1);
	solve(2);
}
