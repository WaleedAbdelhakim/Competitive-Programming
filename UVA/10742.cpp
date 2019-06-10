#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
int prime[N];
vector<int> primes;
void sieve() {
    memset(prime , 1 , sizeof prime);
    prime[0] = prime[1] = 0;
    for (int i = 2 ;i < N ;i++) {
        if (prime[i]) {
            primes.push_back(i);
            for (long long j = i * 1ll * i ;j < N ;j += i)
                prime[j] = 0;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    sieve();    
    int n , c = 1;
    while (scanf("%d" , &n) , n) {
        int ans = 0;
        for (int i = 0 ; primes[i] * 2 < n ;i++) {
            int f = upper_bound(primes.begin() + i + 1 , primes.end() , n - primes[i]) - primes.begin() - 1;
            ans += max(0 , f - i);
        }
        printf("Case %d: %d\n" , c++ , ans);
    }
}
