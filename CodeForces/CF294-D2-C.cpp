#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5 , MOD = 1e9 + 7;
int n , m;
int fact[N];
bool light[N];

int mul(int a , int b) {
    return a * 1ll * b % MOD;
}

int power(int a , int b) {
    if (!b)
        return 1;

    int r = power(a , b / 2);
    r = (r * 1ll * r) % MOD;

    if (b&1)
        return (r * 1ll * a) % MOD;

    return r;
}

int modinv(int x) {
    return power(x , MOD - 2);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    scanf("%d%d" , &n , &m);

    int x;
    for (int i = 0 ; i < m ;i++) {
        scanf("%d" , &x);
        light[x - 1] = 1;
    }

    vector<int> info;
    for (int i = 0 ;i < n ;) {
        int cur = light[i] , cnt = 0;
        while (i < n && light[i] == cur)
            cnt++ , i++;
        info.push_back(cnt);
    }

    fact[0] = 1;
    for (int i = 1 ;i < N ;i++)
        fact[i] = mul(fact[i - 1] , i);

    int ans = fact[n - m];

    bool cur = light[0];
    for (int i = 0 ;i < info.size() ;i++) {
        if (!cur) {
            ans = mul(ans , modinv(fact[info[i]]));
            if (i != 0 && i != info.size() - 1)
                ans = mul(ans , power(2 , info[i] - 1));
        }
        cur = !cur;
    }

    printf("%d" , ans);
}