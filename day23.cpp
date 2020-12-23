#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

struct Node {
    int val;
    Node *next{}, *prev{};

    explicit Node(int val) : val(val) {}

    friend ostream &operator<<(ostream &out, const Node &N) {
        out << N.val;
        return out;
    }
};

struct List {
    Node *H{};

    Node *pushBack(int val) {
        Node *N = new Node(val);
        if (!H) {
            N->next = N->prev = N;
            H = N;
            return N;
        }

        if (H->prev == H) {
            N->next = H;
            N->prev = H;
            H->next = N;
            H->prev = N;
            return N;
        }

        Node *L = H->prev;

        N->next = H;
        N->prev = L;

        L->next = N;
        H->prev = N;
        return N;
    }

    Node *getNodeByValue(int val) {
        Node *N = H;
        do {
            if (N->val == val)
                return N;
            N = N->next;
        } while (N != H);
        return nullptr;
    }

    int maxValue() const {
        int ans = H->val;
        for (Node *N = H->next; N != H; N = N->next)
            ans = max(ans, N->val);
        return ans;
    }

    void deleteFrom(Node *N, int count) {
        for (int i = 1; i <= count; i++) {
            Node *aux = N->next;
            N->prev->next = N->next;
            N->next->prev = N->prev;
            N = aux;
        }
    }

    void insertAfter(Node *&N, const vector<int> &v) {
        for (auto val: v) {
            Node *I = new Node(val);
            I->next = N->next;
            I->prev = N;

            N->next->prev = I;
            N->next = I;

            N = I;
        }
    }

    friend ostream &operator<<(ostream &out, const List &L) {
        Node *N = L.H;
        do {
            out << N->val;
            N = N->next;
            if (N != L.H) out << ' ';
        } while (N != L.H);
        return out;
    }
};

void epoch(List &L, Node *S) {
    vector<int> picked;
    picked.push_back(S->next->val);
    picked.push_back(S->next->next->val);
    picked.push_back(S->next->next->next->val);

    L.deleteFrom(S->next, 3);
    L.H = S;

    int dest = S->val;
    do {
        dest--;
        if (dest == 0)
            dest = L.maxValue();
    } while (find(picked.begin(), picked.end(), dest) != picked.end());

    Node *destNode = L.getNodeByValue(dest);
    assert(destNode != nullptr);

    L.insertAfter(destNode, picked);
}

int main() {
    //vector<int> state{3, 8, 9, 1, 2, 5, 4, 6, 7};
    vector<int> state{3, 6, 8, 1, 9, 5, 7, 4, 2};

    List L{};

    for (auto x: state)
        L.pushBack(x);

    Node *C = L.H;

    for (int e = 1; e <= 100; e++) {
        epoch(L, C);
        C = C->next;
    }

    Node *S = L.getNodeByValue(1);
    Node *N = S->next;

    do {
        cout << N->val;
        N = N->next;
    } while (N != S);
}
