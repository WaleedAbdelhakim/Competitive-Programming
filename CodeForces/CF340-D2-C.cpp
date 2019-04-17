#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int n;
int arr[N];

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    scanf("%d" , &n);

    for (int i = 0 ;i < n ;i++)
        scanf("%d" , arr + i);

    sort(arr , arr + n);

    long long s = 0;
    for (int i = 0 ;i < n ;i++)
        s += arr[i] * (4 * i - 2ll * n + 3);

    int gcd = __gcd(s , n * 1ll);

    printf("%lld %d\n" , s / gcd , n / gcd);
}