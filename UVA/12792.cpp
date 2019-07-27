#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
int nxt[N];

int main() {
    int n;
    while (scanf("%d" , &n) == 1) {
        for (int i = 0 , e = 1 ;i < n / 2 ;i++ , e += 2) nxt[i] = e;
        for (int i = n / 2 , e = 0 ;i < n ;i++ , e += 2) nxt[i] = e;

        int cnt = 1;
        int p = nxt[0];
        while (p != 0) p = nxt[p] , cnt++;

        printf("%d\n" , cnt);
    }
}
