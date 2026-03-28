/**
 * File: Schedule.cpp
 * Author: racsosabe
 * Date: 28/03/2026
 */

#include <iostream>
#include <cstring>
using namespace std;

const int N = 4000000 + 5;
const int L = 10;

struct Node {
    unsigned int priority;
    char name[L];

    Node() {

    }

    bool operator < (const Node &rhs) const {
        if (priority != rhs.priority) return priority < rhs.priority;
        return strcmp(name, rhs.name) < 0;
    }

    bool operator == (const Node &rhs) const {
        return strcmp(name, rhs.name) == 0 and priority == rhs.priority;
    }

    bool operator > (const Node &rhs) const {
        return rhs < *this;
    }
};

int sz;
char s[L];
Node heap[N];

void fix_down(int p, int n) {
    int head = p;
    if (2 * p <= n and heap[2 * p] < heap[head]) {
        head = 2 * p;
    }
    if (2 * p + 1 <= n and heap[2 * p + 1] < heap[head]) {
        head = 2 * p + 1;
    }
    if (head != p) {
        swap(heap[head], heap[p]);
        fix_down(head, n);
    }
}

void fix_up(int x, int n) {
    if (x == 1) return;
    int p = x / 2;
    int head = p;
    if (2 * p <= n and heap[2 * p] < heap[head]) {
        head = 2 * p;
    }
    if (2 * p + 1 <= n and heap[2 * p + 1] < heap[head]) {
        head = 2 * p + 1;
    }
    if (head != p) {
        swap(heap[head], heap[p]);
        fix_up(p, n);
    }
}

Node top() {
    return heap[1];
}

void pop() {
    swap(heap[1], heap[sz--]);
    fix_down(1, sz);
}

void add(Node x) {
    heap[++sz] = x;
    fix_up(sz, sz);
}

void heapify(int n) {
    sz = n;
    for (int i = n / 2; i >= 1; --i) {
        fix_down(i, n);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        unsigned int p;
        cin >> p >> s;
        heap[i].priority = p;
        strcpy(heap[i].name, s);
    }
    heapify(n);
    while (m--) {
        if (sz == 0) break;
        cout << top().name << '\n';
        Node cur = top(); pop();
        if (cur.priority < (1U << 31)) {
            cur.priority <<= 1;
            add(cur);
        }
    }
    return 0;
}
