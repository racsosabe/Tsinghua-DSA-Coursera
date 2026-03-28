/**
 * File: Range.cpp
 * Author: racsosabe
 * Date: 24/03/2026
 */

#include <iostream>
using namespace std;

const int B = 10000;

int f(int* a, int n, int x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mi = lo + (hi - lo) / 2;
        if (a[mi] <= x) lo = mi + 1;
        else hi = mi;
    }
    return lo;
}

void sort(int* a, int n) {
    int* head = new int[B];
    fill_n(head, B, 0);
    for (int i = 0; i < n; ++i) {
        int x = a[i] % B;
        ++head[x];
    }
    int sum = 0;
    for (int i = 0; i < B; ++i) {
        sum += head[i];
        head[i] = sum - head[i];
    }
    int* temp_a = new int[n];
    for (int i = 0; i < n; ++i) {
        int x = a[i] % B;
        temp_a[head[x]++] = a[i];
    }
    fill_n(head, B, 0);
    for (int i = 0; i < n; ++i) {
        int x = temp_a[i] / B;
        ++head[x];
    }
    sum = 0;
    for (int i = 0; i < B; ++i) {
        sum += head[i];
        head[i] = sum - head[i];
    }
    for (int i = 0; i < n; ++i) {
        int x = temp_a[i] / B;
        a[head[x]++] = temp_a[i];
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    int* a = new int[n];
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a, n);
    while(m--) {
        int l, r;
        cin >> l >> r;
        cout << f(a, n, r) - f(a, n, l - 1) << '\n';
    }
    return 0;
}