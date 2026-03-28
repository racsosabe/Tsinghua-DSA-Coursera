/**
 * File: Deduplicate.cpp
 * Author: racsosabe
 * Date: 27/03/2026
 */

#include <iostream>
#include <cstring>
using namespace std;

const int BUCKETS = 200003;
const int MOD = 1e9 + 7;
const int N = 600000;
const int L = 41;
const int B = 31;

int n;
int e;
int id[N];
int cnt[N];
int nxt[N];
char s[N][L];
int last[BUCKETS];

int get_hash(int x) {
    int res = 0;
    for (int i = 0; s[x][i]; ++i) {
        res = (1LL * res * B + s[x][i] - 'a') % MOD;
    }
    return res;
}

int check(int x) {
    int H = get_hash(x);
    int P = H % BUCKETS;
    for (int e = last[P]; ~e; e = nxt[e]) {
        int cur_id = id[e];
        if (strcmp(s[x], s[cur_id]) == 0) {
            return ++cnt[e];
        }
    }
    id[e] = x;
    nxt[e] = last[P];
    cnt[e] = 1;
    last[P] = e++;
    return cnt[e - 1];
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    fill_n(last, BUCKETS, -1);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        if (check(i) == 2) {
            cout << s[i] << '\n';
        }
    }
    return 0;
}
