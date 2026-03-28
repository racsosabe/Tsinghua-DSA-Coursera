/**
 * File: Cycle.cpp
 * Author: racsosabe
 * Date: 28/03/2026
 */

#include <iostream>
#include <cstring>
using namespace std;

const int N = 100000 + 5;

char s[N];
char t[N];
int pi[N];

int main() {
    cin.tie(0)->sync_with_stdio(false);
    while(cin >> s >> t) {
        if(strlen(s) != strlen(t)) {
            cout << "NO" << '\n';
            continue;
        }
        int n = strlen(s);
        int k = 0;
        pi[0] = 0;
        for (int i = 1; i < n; ++i) {
            while (k > 0 and s[k] != s[i]) k = pi[k - 1];
            if (s[i] == s[k]) ++k;
            pi[i] = k;
        }
        k = 0;
        bool found = false;
        for (int id = 0; id < 2; ++id) {
            for (int i = 0; i < n; ++i) {
                while (k > 0 and s[k] != t[i]) k = pi[k - 1];
                if (s[k] == t[i]) ++k;
                if (k == n) {
                    found = true;
                    k = pi[k - 1];
                }
            }
        }
        cout << (found ? "YES" : "NO") << '\n';
    }
    return 0;
}
