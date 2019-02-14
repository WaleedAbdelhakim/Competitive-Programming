// hard code : ideone.com/xkDhVz

#include <bits/stdc++.h>

using namespace std;

int a[] = {0 , 0 , 1, 2, 9, 44, 265, 1854, 14833, 133496, 1334961, 14684570, 176214841};
int b[] = {0 , 0 , 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T , n;
    scanf("%d" , &T);

    while (T--) {
        scanf("%d" , &n);
        printf("%d/%d\n" , a[n] , b[n]);
    }
}