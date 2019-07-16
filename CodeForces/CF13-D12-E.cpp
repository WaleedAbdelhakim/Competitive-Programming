#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int n , sz , arr[N] , nxt[N] , jumps[N];

void build() {
    sz = sqrt(n) + 1;
    for (int i = 0 ;i < n ;i++) {
        int p = i;
        while (p < n && p / sz == i / sz)
            p += arr[p] , jumps[i]++;
        nxt[i] = p;
    }
}

void update(int i , int v) {
    arr[i] = v;
    for (int j = i ;j >= 0 && j / sz == i / sz ;j--) {
        jumps[j] = 1;
        nxt[j] = j + arr[j];
        if (nxt[j] < n && nxt[j] / sz == j / sz)
            jumps[j] += jumps[nxt[j]] , nxt[j] = nxt[nxt[j]];
    }
}

void query(int p) {
    int cnt = 0;
    while (nxt[p] < n)
        cnt += jumps[p] , p = nxt[p];
    while (p + arr[p] < n)
        p += arr[p] , cnt++;
    printf("%d %d\n" , p +  1 , cnt + 1);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int m;
    scanf("%d%d" , &n , &m);
    for (int i = 0 ;i < n ;i++)
        scanf("%d" , arr + i);

    build();

    int type , a , b;
    while (m--) {
        scanf("%d%d" , &type,&a);
        if (type == 1) {
            query(a - 1);
        } else {
            scanf("%d" , &b);
            update(a - 1 , b);
        }
    }
}