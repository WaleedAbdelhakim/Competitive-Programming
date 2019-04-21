#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
int n , k;
int mx[N];
vector<int> factors[N];

void sieve() {
    for (int i = 2 ;i < N ;i++)
        if (!factors[i].size())
            for (int j = i ;j < N ;j += i)
                factors[j].push_back(i);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    sieve();
    scanf("%d%d" , &n , &k);
    int x;
    for (int i = 0 ;i < n ;i++) {
        scanf("%d" , &x);
        for (int j : factors[x]) {
            int cnt = 0 , t = x;
            while (t % j == 0)
                cnt++ , t /= j;
            mx[j] = max(mx[j] , cnt);
        }
    }

    for (int j : factors[k]) {
        int cnt = 0 , t = k;
        while (t % j == 0)
            cnt++ , t /= j;
        if (mx[j] < cnt) {
            puts("No");
            return 0;
        }
    }

    puts("Yes");
}