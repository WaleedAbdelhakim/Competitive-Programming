#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
bool badR[N] , badC[N];

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int n , m , r , c;
    scanf("%d%d" , &n , &m);

    while (m--) {
        scanf("%d%d" , &r , &c);
        badR[r] = badC[c] = 1;
    }

    int ans = n&1 ? (!badR[(n + 1) / 2] || !badC[(n + 1) / 2]) : 0;
    for (int i = 2 ;i * 2 <= n ;i++)
        ans += !badR[i] + !badC[i] + !badR[n - i + 1] + !badC[n - i + 1];

    printf("%d" , ans);
}