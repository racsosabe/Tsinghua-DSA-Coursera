/**
 * File: LightHouse.cpp
 * Author: racsosabe
 * Date: 24/03/2026
 */

#include <iostream>
using namespace std;

const int N = 4000001;

int n;
int v[N];
int w[N];
int X[N];
int Y[N];

void fix_down(int p, int n) {
	int head = p;
	if(2 * p <= n and X[2 * p] > X[head]) {
		head = 2 * p;
	}
	if(2 * p + 1 <= n and X[2 * p + 1] > X[head]) {
		head = 2 * p + 1;
	}
	if(head != p) {
		swap(X[head], X[p]);
		swap(Y[head], Y[p]);
		fix_down(head, n);
	}
}

void heap_sort() {
	for (int i = n / 2; i >= 1; --i) {
		fix_down(i, n);
	}
	for (int i = n; i > 1; --i) {
		swap(X[1], X[i]);
		swap(Y[1], Y[i]);
		fix_down(1, i - 1);
	}
}

long long merge(int l, int r) {
	int mi = (l + r) / 2;
	int ptr = l;
	int ptr_l = l;
	long long res = 0;
	for (int i = mi + 1; i <= r; ++i) {
		while(ptr_l <= mi and v[ptr_l] < v[i]) {
			w[ptr++] = v[ptr_l++];
		}
		res += ptr_l - l;
		w[ptr++] = v[i];
	}
	while (ptr_l <= mi) {
		w[ptr++] = v[ptr_l++];
	}
	copy(w + l, w + r + 1, v + l);
	return res;
}

long long inversions(int l, int r) {
	if (l == r) return 0;
	int mi = (l + r) / 2;
	long long res = inversions(l, mi) + inversions(mi + 1, r);
	res += merge(l, r);
	return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", X + i, Y + i);
    }
	heap_sort();
	for (int i = 0; i < n; ++i) {
		v[i] = Y[i + 1];
	}
    printf("%lld\n", inversions(0, n - 1));
    return 0;
}