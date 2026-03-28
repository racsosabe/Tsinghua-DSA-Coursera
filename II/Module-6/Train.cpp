/**
 * File: Train.cpp
 * Author: racsosabe
 * Date: 26/03/2026
 */

#include <iostream>
using namespace std;

const int MASK = 63;

void set_bit(unsigned long long* bitset, int position, int bit) {
    int id = position >> 6;
    if (bit) {
        bitset[id] |= (1ULL << (position & MASK));
    }
    else {
        bitset[id] &= ~(1ULL << (position & MASK));
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m;
    scanf("%d %d", &n, &m);
    unsigned long long pot[64];
    pot[0] = 1;
    for (int i = 1; i < 64; ++i) {
        pot[i] = pot[i - 1] << 1;
    }
    int len = (2 * n + 63) >> 6;
    unsigned long long *bitset = new unsigned long long[len];
    fill_n(bitset, len, 0);
    int st_len = 0;
    int *st = new int[n];
    int ptr = 1;
    int ops = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        while (ptr <= n and (st_len == 0 or st[st_len - 1] != x)) {
            set_bit(bitset, ops++, 1);
            st[st_len++] = ptr++;
            if (st_len > m) {
                puts("No");
                return 0;
            }
        }
        if (st_len == 0 or st[st_len - 1] != x) {
            puts("No");
            return 0;
        }
        --st_len;
        set_bit(bitset, ops++, 0);
    }
    for (int i = 0; i < 2 * n; ++i) {
        int id = i >> 6;
        int pos = i & MASK;
        if (bitset[id] & pot[pos]) {
            puts("push");
        }
        else {
            puts("pop");
        }
    }
    return 0;
}