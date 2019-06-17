#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

long long power(long long a , long long b) {
    if (!b) return 1;
    long long r = power(a , b / 2);
    r = r * r % MOD;
    if (b&1) return r * a % MOD;
    return r;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int n , m , k , p = 1;
    scanf("%d%d%d" , &n , &m , &k);
    if (k > n || k == 1) p = n;
    else if (k == n) p = (n + 1) / 2;
    else if (k&1) p = 2;
    printf("%d" , power(m , p));
}