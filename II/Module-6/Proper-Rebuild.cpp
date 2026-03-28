/**
 * File: Proper-Rebuild.cpp
 * Author: racsosabe
 * Date: 26/03/2026
 */

#include <iostream>
using namespace std;

int* read_inverse_perm(int n) {
    int* perm = new int[n];
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        --x;
        perm[x] = i;
    }
    return perm;
}

void build(int l_pre, int r_pre, int l_post, int r_post, int* pre, int* pos_post, int* L, int* R) {
    int x = pre[l_pre];
    if (l_pre == r_pre) {
        L[x] = R[x] = -1;
        return;
    }
    int left_child = pre[l_pre + 1];
    int r_post_left_child = pos_post[left_child];
    int left_child_size = r_post_left_child - l_post + 1;
    int right_child = pre[l_pre + left_child_size + 1];
    build(l_pre + 1, l_pre + left_child_size, l_post, r_post_left_child, pre, pos_post, L, R);

    build(l_pre + left_child_size + 1, r_pre, l_post + left_child_size, r_post - 1, pre, pos_post, L, R);
    L[x] = left_child;
    R[x] = right_child;
}

void inorder(int u, int* L, int* R) {
    if (~L[u]) {
        inorder(L[u], L, R);
    }
    printf("%d ", u + 1);
    if (~R[u]) {
        inorder(R[u], L, R);
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    scanf("%d", &n);
    int* pre = new int[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", pre + i);
        --pre[i];
    }
    int* pos_post = read_inverse_perm(n);
    int* L = new int[n];
    int* R = new int[n];
    build(0, n - 1, 0, n - 1, pre, pos_post, L, R);
    inorder(pre[0], L, R);
    putchar('\n');
    return 0;
}