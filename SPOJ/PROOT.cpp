// explanation : www.apfloat.org/prim.html

#include <bits/stdc++.h>

using namespace std;

long long power(long long a , long long b , int MOD) {
    if (!b) return 1;
    long long r = power(a , b / 2 , MOD);
    r = r * r % MOD;
    if (b&1) return r * a % MOD;
    return r;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int p , n;
    while (scanf("%d%d" , &p , &n) , n + p) {
        vector<int> factors;
        int c = p - 1;
        for (int i = 2 ;i * i <= c;i++)  {
            if (c % i == 0) {
                factors.push_back(i);
                while (c % i == 0)
                    c /= i;
            }
        }

        if (c != 1) factors.push_back(c);

        int x;
        while (n--) {
            scanf("%d" , &x);
            if (x % p == 0) {
                puts("NO");
                continue;
            }

            bool good = 1;
            for (int i = 0 ;good && i < factors.size();i++)
                good &= power(x , (p - 1) / factors[i] , p) != 1;

            puts(good ? "YES" : "NO");
        }
    }
}