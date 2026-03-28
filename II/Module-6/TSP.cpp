/**
 * File: TSP.cpp
 * Author: racsosabe
 * Date: 26/03/2026
 */

#include <iostream>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m;
    scanf("%d %d", &n, &m);
    int *last = new int[n];
    fill_n(last, n, -1);
    int *to = new int[m];
    int *nxt = new int[m];
    int *in = new int[n];
    fill_n(in, n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        --u; --v;
        to[i] = v;
        nxt[i] = last[u];
        last[u] = i;
        ++in[v];
    }
    int *Q = new int[n];
    int at = 0, sz = 0;
    for (int i = 0; i < n; ++i) {
        if (in[i] == 0) {
            Q[sz++] = i;
        }
    }
    int ptr = 0;
    int *topo = new int[n];
    while (at < sz) {
        int u = Q[at++];
        topo[ptr++] = u;
        for (int e = last[u]; ~e; e = nxt[e]) {
            int v = to[e];
            --in[v];
            if (in[v] == 0) {
                Q[sz++] = v;
            }
        }
    }
    int *memo = new int[n];
    fill_n(memo, n, 0);
    int res = 0;
    for (int i = n - 1; i >= 0; --i) {
        int x = topo[i];
        memo[x] = 1;
        for (int e = last[x]; ~e; e = nxt[e]) {
            int v = to[e];
            if (memo[x] < 1 + memo[v]) {
                memo[x] = 1 + memo[v];
            }
        }
        res = max(res, memo[x]);
    }
    printf("%d\n", res);
    return 0;
}