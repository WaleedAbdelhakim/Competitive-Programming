#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e6 + 3;
const int N = 1e6 + 5;
long long f[N];

long long mul(long long a , long long b) {
    return a * b % MOD;
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

long long nCr(long long n , long long r){
    return mul(f[n] , mod_inv(mul(f[n - r] , f[r])));
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    f[0] = 1;
    for(int i = 1 ; i < N ;i++)
        f[i] = mul(f[i - 1] , i);

    int n , c;
    scanf("%d%d" , &n, &c);
    printf("%d" , (nCr(n + c , c) + MOD - 1) % MOD);
}
