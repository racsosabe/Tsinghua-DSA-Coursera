/**
 * File: Broadcast.cpp
 * Author: racsosabe
 * Date: 27/03/2026
 */

#include <iostream>
using namespace std;

const int M = 2 * 30000 + 5;
const int N = 10000 + 5;

int n;
int m;
int e;
int Q[N];
int to[M];
int nxt[M];
int last[N];
int color[N];

void add_edge(int u, int v) {
    to[e] = v;
    nxt[e] = last[u];
    last[u] = e++;
}

bool bipartite() {
    fill_n(color, n, -1);
    for (int i = 0; i < n; ++i) {
        if (~color[i]) continue;
        int at = 0, sz = 0;
        Q[sz++] = i;
        color[i] = 0;
        while (at < sz) {
            int u = Q[at++];
            for (int e = last[u]; ~e; e = nxt[e]) {
                int v = to[e];
                if (color[v] == color[u]) return false;
                if (~color[v]) continue;
                color[v] = color[u] ^ 1;
                Q[sz++] = v;
            }
        }
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m;
    fill_n(last, n, -1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        add_edge(u, v);
        add_edge(v, u);
    }
    cout << (bipartite() ? 1 : -1) << '\n';
    return 0;
}
