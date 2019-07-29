#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;
int arr[N] , pf[N] , f[N];
int prime[N] , bad[N];

void sieve() {
    memset(prime , 1 , sizeof prime);
    prime[0] = prime[1] = 0;
    for (int i = 2 ;i < N ;i++)
        if (prime[i])
            for (int j = i ;j < N ;j += i)
                prime[j] = 0 , pf[j]++ , bad[j] |= j % (i * i) == 0;
}

long long nC4(long long n) {
    return (n * (n - 1) * (n - 2) * (n - 3)) / 24;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    sieve();

    int n;
    while (scanf("%d" , &n) == 1) {
        memset(f , 0 , sizeof f);
        for (int i = 0 ;i < n ;i++) {
            scanf("%d" , arr + i);
            f[arr[i]]++;
        }

        long long ans = nC4(n);
        for (int i = 2 ;i < N ;i++) if (!bad[i]) {
            int cnt = 0;
            for (int j = i ;j < N ;j += i) cnt += f[j];
            ans += pf[i]&1 ? -nC4(cnt) : nC4(cnt);
        }

        printf("%lld\n" , ans);
    }
}