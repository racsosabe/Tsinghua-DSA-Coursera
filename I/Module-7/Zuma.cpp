/**
 * File: Zuma.cpp
 * Author: racsosabe
 * Date: 24/03/2026
 */

#include <iostream>
#include <cstring>
using namespace std;

const int N = 2 * 10000 + 5;

int n;
int len;
char s[N];
char ch[N];
int cnt[N];

void build() {
    int l = 0;
    while (l < n) {
        int r = l;
        while (r < n and s[l] == s[r]) ++r;
        ch[len] = s[l];
        cnt[len] = r - l;
        ++len;
        l = r;
    }
}

pair<int, char> get_char(int pos) {
    ++pos;
    for (int i = 0; i < len; ++i) {
        if (cnt[i] >= pos) return make_pair(i, ch[i]);
        pos -= cnt[i];
    }
    return {-1, '$'};
}

void fix(int to_erase) {
    if (cnt[to_erase] < 3) return;
    n -= cnt[to_erase];
    int r;
    int l = to_erase - 1;
    for (r = to_erase + 1; r < len; ++r) {
        if (l >= 0 and ch[l] == ch[r]) {
            cnt[l] += cnt[r];
            if (cnt[l] >= 3) {
                n -= cnt[l];
                --l;
            }
            else {
                ++r;
                break;
            }
        }
        else break;
    }
    ++l;
    for (int i = r; i < len; ++i) {
        ch[l] = ch[i];
        cnt[l++] = cnt[i];
    }
    len = l;
}

void split(int block, int pos, char c) {
    int sum = 0;
    for (int i = 0; i < block; i++) {
        sum -= cnt[i];
    }
    pos -= sum;
    for (int i = len - 1; i > block; --i) {
        swap(ch[i], ch[i + 2]);
        swap(cnt[i], cnt[i + 2]);
    }
    ch[block + 2] = ch[block];
    cnt[block] = 1;
    cnt[block + 2] = 1;
    ch[block + 1] = c;
    cnt[block + 1] = 1;
    len += 2;
}

void update(int pos, char c) {
    if (pos == n) {
        ++n;
        if (len > 0 and ch[len - 1] == c) {
            ++cnt[len - 1];
            if (cnt[len - 1] >= 3) {
                n -= cnt[len - 1];
                --len;
            }
        }
        else {
            ch[len] = c;
            cnt[len++] = 1;
        }
        return;
    }
    ++n;
    if (pos == 0) {
        if (ch[0] == c) {
            ++cnt[0];
            if (cnt[0] >= 3) {
                n -= cnt[0];
                for (int i = 1; i < len; ++i) {
                    swap(ch[i - 1], ch[i]);
                    swap(cnt[i - 1], cnt[i]);
                }
                --len;
            }
        }
        else {
            for (int i = len; i > 0; --i) {
                swap(ch[i - 1], ch[i]);
                swap(cnt[i - 1], cnt[i]);
            }
            cnt[0] = 1;
            ch[0] = c;
            ++len;
        }
        return;
    }

    pair<int, char> L = get_char(pos - 1);
    pair<int, char> R = get_char(pos);
    int id_l = L.first, id_r = R.first;
    char l = L.second, r = R.second;
    if (l == r) {
        if (l == c) {
            ++cnt[id_l];
            fix(id_l);
        }
        else {
            split(id_l, pos, c);
        }
    }
    else {
        if (l == c) {
            ++cnt[id_l];
            fix(id_l);
        }
        else if (r == c) {
            ++cnt[id_r];
            fix(id_r);
        }
        else {
            for (int i = len - 1; i >= id_r; --i) {
                swap(ch[i], ch[i + 1]);
                swap(cnt[i], cnt[i + 1]);
            }
            ch[id_r] = c;
            cnt[id_r] = 1;
            ++len;
        }
    }
}

void print() {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < cnt[i]; ++j) {
            putchar(ch[i]);
        }
    }
    putchar('\n');
}

int read_s() {
    int n = 0;
    char c = getchar();
    while(c != '\n' and c != '\r') {
        s[n++] = c;
        c = getchar();
    }
    return n;
}

int main() {
    n = read_s();
    int q;
    scanf("%d", &q);
    build();
    while (q--) {
        int pos;
        char c;
        scanf("%d %c\n", &pos, &c);
        update(pos, c);
        if (n == 0) puts("-");
        else print();
    }
    return 0;
}
