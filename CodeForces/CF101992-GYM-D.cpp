#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5 , MOD = 1e9 + 7;
int n;
int arr[N] , f[N] , inv[N] , pairs[N];
vector<int> d[N];

int mul(int a , int b) {
    return a * 1ll * b % MOD;
}

int add(int a , int b) {
    a += b;
    while (a >= MOD) a -= MOD;
    while (a < 0) a += MOD;
    return a;
}

long long power(long long a , long long b) {
    if (!b) return 1;
    long long r = power(a , b / 2);
    r = mul(r , r);
    if (b&1) return mul(r , a);
    return r;
}

long long mod_inv(long long x) {
    return power(x , MOD - 2);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r"  ,stdin);
#endif
    int T;
    scanf("%d" , &T);
    while (T--) {
        scanf("%d" , &n);

        int max_val = 0;
        for (int i = 0 ;i < n ;i++) {
            scanf("%d" , arr + i);
            max_val = max(max_val , arr[i]);
            f[arr[i]]++;
        }

        int ans = 0;
        for (int gcd = max_val ; gcd >= 1 ; gcd--) {
            int sum = 0;
            pairs[gcd] = 0;
            for (int m = gcd ; m <= max_val ; m += gcd) sum = add(sum , mul(m , f[m]));
            for (int m = gcd ; m <= max_val ; m += gcd) pairs[gcd] = add(pairs[gcd] , mul(sum , mul(f[m] , m)));
            for (int m = gcd + gcd ; m <= max_val ; m += gcd) pairs[gcd] = add(pairs[gcd], -pairs[m]);
            ans = add(ans , mul(pairs[gcd] , mod_inv(gcd)));
        }

        printf("%d\n" , ans);
        memset(f , 0 , (max_val + 1) * sizeof f[0]);
    }
}