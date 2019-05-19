#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
bool overflow(long long a, long long b) {
    long double res = a * b;
    if (a == 0 || b == 0 || res / b == a)
        return false;
    return true;
}
long long nth_root(long long x , int cnt) {
    long long l = 1 , r = x , theOne = -1;
    while (l <= r) {
        long long mid = (l + r) / 2 , ans = 1;
        bool ovf = 0;
        for (int i = 0 ;i < cnt ;i++) {
            ovf |= overflow(ans , mid);
            ans *= mid;
        }

        if (ans == x) {
            theOne = mid;
            break;
        }

        if (ovf || ans >= x)
            r = mid - 1;
        else
            l = mid + 1;
    }

    return theOne;
}

int mul(int a , int b) {
    return a * 1ll * b % MOD;
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int n;
    cin >> n;

    map<long long , int> info , other;
    set<long long> primes;

    long long x;
    for (int i = 0 ;i < n ;i++) {
        cin >> x;
        bool con = 0;
        for (int j = 4 ;j >= 2 ;j--) {
            long long c = nth_root(x , j);
            if (~c) {
                info[c] += j;
                con = 1;
                primes.insert(c);
                break;
            }
        }
        if (con) continue;
        other[x]++;
    }

    for (auto &p : other) {
        for (auto &pp : primes) {
            long long gcd = __gcd(p.first , pp);
            if (gcd != 1) {
                primes.insert(gcd);
                primes.insert(p.first / gcd);
            }
        }

        for (auto &pp : other) {
            if (p.first == pp.first) continue;
            long long gcd = __gcd(p.first , pp.first);
            if (gcd != 1) {
                primes.insert(gcd);
                primes.insert(p.first / gcd);
            }
        }
    }

    int ans = 1;
    for (auto &x : other) {
        bool f = 0;
        for (auto &p : primes) {
            if (x.first % p == 0) {
                info[p] += x.second;
                info[x.first / p] += x.second;
                f = 1;
                break;
            }
        }
        if (!f)
            ans = mul(ans , mul((x.second + 1) , (x.second + 1)));
    }
    for (auto &p : info) {
        ans = mul(ans , p.second + 1);
    }
    cout << ans << endl;
}