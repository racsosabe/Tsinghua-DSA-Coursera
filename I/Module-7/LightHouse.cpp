/**
 * File: LightHouse.cpp
 * Author: racsosabe
 * Date: 24/03/2026
 */

#include <iostream>
using namespace std;

const int N = 4000000;

int X[N];
int Y[N];



int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &X[i], &Y[i]);
    }
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (X[i] < X[j] and Y[i] < Y[j]) {
                ++res;
            }
            if (X[i] > X[j] and Y[i] > Y[j]) {
                ++res;
            }
        }
    }
    printf("%lld\n", res);
    return 0;
}