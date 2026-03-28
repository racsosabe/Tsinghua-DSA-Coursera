/**
 * File: Temperature.cpp
 * Author: racsosabe
 * Date: 27/03/2026
 */

#include <iostream>
#include "temperature.h"
using namespace std;

const int N = 50000 + 2;

int n;
int x[N];
int y[N];
int T[N];
int m_x;
int m_y;
int *values_x;
int *values_y;
int* ft[N];
long long* sum[N];
int* ft_values[N];
int sizes[N];

void merge(int* a, int* b, int l, int r) {
    int mi = (l + r) / 2;
    int ptr = l;
    int ptr_r = mi + 1;
    for (int i = l; i <= mi; ++i) {
        while (ptr_r <= r && a[ptr_r] <= a[i]) {
            b[ptr++] = a[ptr_r++];
        }
        b[ptr++] = a[i];
    }
    while (ptr_r <= r) {
        b[ptr++] = a[ptr_r++];
    }
    copy(b + l, b + r + 1, a + l);
}

void merge_sort(int* a, int* b, int l, int r) {
    if (l == r) return;
    int mi = (l + r) / 2;
    merge_sort(a, b, l, mi);
    merge_sort(a, b, mi + 1, r);
    merge(a, b, l, r);
}

void sort(int* begin, int* end) {
    int n = end - begin;
    int* tmp = new int[n];
    merge_sort(begin, tmp, 0, n - 1);
    delete[] tmp;
}

int lower_bound(const int* values, int n, int x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mi = lo + (hi - lo) / 2;
        if (values[mi] < x) lo = mi + 1;
        else hi = mi;
    }
    return lo;
}

int upper_bound(const int* values, int n, int x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mi = lo + (hi - lo) / 2;
        if (values[mi] <= x) lo = mi + 1;
        else hi = mi;
    }
    return lo;
}

int compress(int* X, int* &values, int sz) {
    values = new int[sz];
    for (int i = 0; i < sz; ++i) {
        values[i] = X[i];
    }
    sort(values, values + sz);
    int at = 0;
    for (int i = 0; i < sz; ++i) {
        if (i == 0 or values[i - 1] != values[i]) {
            values[at++] = values[i];
        }
    }
    for (int i = 0; i < sz; ++i) {
        X[i] = lower_bound(values, at, X[i]);
    }
    return at;
}

void add_size(int pos) {
    ++pos;
    while (pos <= m_x) {
        ++sizes[pos];
        pos += (-pos) & pos;
    }
}

void add_value(int pos, const int val) {
    ++pos;
    while (pos <= m_x) {
        ft_values[pos][sizes[pos]] = val;
        ++sizes[pos];
        pos += (-pos) & pos;
    }
}

template<typename int_type>
void update(int_type* &ft, int pos, int val, int n) {
    ++pos;
    while (pos <= n) {
        ft[pos] += val;
        pos += (-pos) & pos;
    }
}

void update(int pos, int val, int temp) {
    ++pos;
    while (pos <= m_x) {
        const int to = upper_bound(ft_values[pos], sizes[pos], val) - 1;
        update(ft[pos],  to, 1, sizes[pos]);
        update(sum[pos],  to, temp, sizes[pos]);
        pos += (-pos) & pos;
    }
}

template<typename int_type>
int_type get_sum_ft(int_type* &ft, int pos) {
    ++pos;
    int_type res = 0;
    while (pos > 0) {
        res += ft[pos];
        pos &= pos - 1;
    }
    return res;
}

long long get_sum(int x, int y) {
    ++x;
    long long res = 0;
    while (x > 0) {
        const int to = upper_bound(ft_values[x], sizes[x], y) - 1;
        res += get_sum_ft<long long>(sum[x], to);
        x &= x - 1;
    }
    return res;
}

int get_cnt(int x, int y) {
    ++x;
    int res = 0;
    while (x > 0) {
        const int to = upper_bound(ft_values[x], sizes[x], y) - 1;
        res += get_sum_ft<int>(ft[x], to);
        x &= x - 1;
    }
    return res;
}

void preprocess() {
    m_x = compress(x, values_x, n);
    for (int i = 0; i < n; ++i) {
        add_size(x[i]);
    }
    for (int i = 1; i <= m_x; ++i) {
        ft_values[i] = new int[sizes[i] + 1];
        sizes[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        add_value(x[i], y[i]);
    }
    for (int i = 1; i <= m_x; ++i) {
        int* carry_values = nullptr;
        sizes[i] = compress(ft_values[i], carry_values, sizes[i]);
        ft_values[i] = new int[sizes[i]];
        copy(carry_values, carry_values + sizes[i], ft_values[i]);
        ft[i] = new int[sizes[i] + 1];
        sum[i] = new long long[sizes[i] + 1];
        fill_n(ft[i], sizes[i] + 1, 0);
        fill_n(sum[i], sizes[i] + 1, 0LL);
    }
    for (int i = 0; i < n; ++i) {
        update(x[i], y[i], T[i]);
    }
}

int solve(int a, int b, int c, int d) {
    if (n == 0) return 0;
    --a; --b;
    a = upper_bound(values_x, m_x, a) - 1;
    c = upper_bound(values_x, m_x, c) - 1;
    if (a > c) return 0;
    int cnt = get_cnt(c, d) + get_cnt(a, b) - get_cnt(c, b) - get_cnt(a, d);
    long long s = get_sum(c, d) + get_sum(a, b) - get_sum(c, b) - get_sum(a, d);
    return cnt == 0 ? 0 : s / cnt;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    n = GetNumOfStation();
    for (int i = 0; i < n; ++i) {
        GetStationInfo(i, &x[i], &y[i], &T[i]);
    }
    if (n > 0) {
        preprocess();
    }
    int x1, y1, x2, y2;
    while (GetQuery(&x1, &y1, &x2, &y2)) {
        Response(solve(x1, y1, x2, y2));
    }
    return 0;
}
