/**
 * File: Toy.cpp
 * Author: racsosabe
 * Date: 28/03/2026
 */

#include <iostream>
using namespace std;

const int PERM = 40320;
const int L = 8;


int f[L];
int D[PERM];
int Q[PERM][L];

int get_id(const int* a) {
    int mask = (1 << L) - 1;
    int res = 0;
    for (int i = 0; i < L; ++i) {
        const int rnk = __builtin_popcount(mask & ((1 << a[i]) - 1));
        res += rnk * f[L - 1 - i];
        mask ^= (1 << a[i]);
    }
    return res;
}

int id(const int at) {
    int mask = (1 << L) - 1;
    int res = 0;
    for (int i = 0; i < L; ++i) {
        const int rnk = __builtin_popcount(mask & ((1 << Q[at][i]) - 1));
        res += rnk * f[L - 1 - i];
        mask ^= (1 << Q[at][i]);
    }
    return res;
}

void swap_rows(int at) {
    for(int i = 0; i < 4; ++i) {
        swap(Q[at][i], Q[at][i + 4]);
    }
}

void cyclic_shift(int at) {
    for(int i = 3; i > 0; --i) {
        swap(Q[at][i - 1], Q[at][i]);
        swap(Q[at][i + 3], Q[at][i + 4]);
    }
}

void reverse_cyclic_shift(int at) {
    for(int i = 0; i < 3; ++i) {
        swap(Q[at][i + 1], Q[at][i]);
        swap(Q[at][i + 5], Q[at][i + 4]);
    }
}

void clockwise_rotate(int at) {
    swap(Q[at][1], Q[at][5]);
    swap(Q[at][5], Q[at][6]);
    swap(Q[at][6], Q[at][2]);
}

void reverse_clockwise_rotate(int at) {
    swap(Q[at][6], Q[at][2]);
    swap(Q[at][5], Q[at][6]);
    swap(Q[at][1], Q[at][5]);
}

void BFS() {
    int at = 0;
    int sz = 1;
    for (int i = 0; i < 4; ++i) Q[0][i] = i;
    for (int i = 4; i < L; ++i) Q[0][i] = 11 - i;
    fill_n(D, PERM, -1);
    D[id(0)] = 0;
    while (at < sz) {
        int u = id(at);
        swap_rows(at);
        int v = id(at);
        if (D[v] == -1) {
            D[v] = D[u] + 1;
            for (int j = 0; j < L; ++j) Q[sz][j] = Q[at][j];
            ++sz;
        }
        swap_rows(at);
        reverse_cyclic_shift(at);

        v = id(at);
        if (D[v] == -1) {
            D[v] = D[u] + 1;
            for (int j = 0; j < L; ++j) Q[sz][j] = Q[at][j];
            ++sz;
        }
        cyclic_shift(at);
        reverse_clockwise_rotate(at);
        v = id(at);
        if (D[v] == -1) {
            D[v] = D[u] + 1;
            for (int j = 0; j < L; ++j) Q[sz][j] = Q[at][j];
            ++sz;
        }
        clockwise_rotate(at);
        ++at;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    f[0] = 1;
    for (int i = 1; i < L; ++i) f[i] = i * f[i - 1];
    BFS();
    int t;
    cin >> t;
    int a[L];
    while (t--) {
        for (int i = 0; i < 4; ++i) {
            cin >> a[i];
            --a[i];
        }
        for (int i = L - 1; i >= 4; --i) {
            cin >> a[i];
            --a[i];
        }
        cout << D[get_id(a)] << '\n';
    }
    return 0;
}
