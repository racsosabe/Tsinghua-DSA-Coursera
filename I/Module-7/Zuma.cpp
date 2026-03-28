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

void update(int pos, char c) {
    s[n++] = c;
    s[n] = '\0';
    for (int i = n - 1; i > pos; --i) {
        swap(s[i], s[i - 1]);
    }
    int l = pos;
    while (l > 0 and s[l] == s[l - 1]) --l;
    int r = pos;
    while (r + 1 < n and s[r] == s[r + 1]) ++r;
    if (r - l + 1 >= 3) {
        --l; ++r;
        while (l >= 0 and r < n) {
            if (s[l] != s[r]) break;
            int cnt_l = 0;
            while (l - cnt_l >= 0 and s[l - cnt_l] == s[l]) ++cnt_l;
            int cnt_r = 0;
            while (r + cnt_r < n and s[r + cnt_r] == s[r]) ++cnt_r;
            if (cnt_l + cnt_r < 3) break;
            l -= cnt_l;
            r += cnt_r;
        }
        if (l == -1 and r == n) {
            n = 0;
        }
        else {
            ++l;
            for (int i = r; i < n; ++i) {
                s[l++] = s[i];
            }
            n = l;
        }
    }
    s[n] = '\0';
}

int read_s() {
    int n = 0;
    char c = getchar();
    while(c != '\n' and c != '\r') {
        s[n++] = c;
        c = getchar();
    }
    s[n] = '\0';
    return n;
}

void print() {
    printf("%s\n", s);
}

int main() {
    n = read_s();
    int q;
    scanf("%d", &q);
    while (q--) {
        int pos;
        char c;
        scanf("%d %c", &pos, &c);
        update(pos, c);
        if (n == 0) puts("-");
        else print();
    }
    return 0;
}
