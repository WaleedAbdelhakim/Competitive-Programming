#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 9;

int add(int a , int b) {
    a += b;
    while (a >= MOD)
        a -= MOD;
    while (a < 0)
        a += MOD;
    return a;
}

int mul(int a , int b) {
    return a * 1ll * b % MOD;
}

long long power(long long a , long long b) {
    if (!b) return 1;
    long long r = power(a , b / 2);
    r = r * r % MOD;
    if (b&1) return r * a % MOD;
    return r;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int n , yes , k , no;
    scanf("%d%d%d" , &n , &yes , &k);
    no = n - yes;

    if (yes <= (no + 1ll) * (k - 1)) {
        printf("%d" , yes);
        return 0;
    }

    int r = yes - no * (k - 1);
    int full = r / k;
    int rem = r % k;
    int f = mul(add(power(2 , full + 1) , -2) , k);
    int s = add(rem , no * (k - 1));
    
    printf("%d" , add(f , s));
}
