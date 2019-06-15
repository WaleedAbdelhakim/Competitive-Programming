#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int add(int a , int b) {
    a += b;
    while (a >= MOD)
        a -= MOD;
    return a;
}

int mul(int a , int b) {
    return a * 1ll * b % MOD;
}

struct median_tracker {
    priority_queue<long long> a;
    priority_queue<long long , vector<long long> , greater<long long> > b;

    long long get_mid() {
        return a.top();
    }

    void insert(long long x) {
        a.size() == b.size() ? b.push(x) : a.push(x);
        if (b.size() > a.size()) a.push(b.top()) , b.pop();
        if (a.size() - 1 > b.size()) b.push(a.top()) , a.pop();
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T, a, b, c, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &a, &b, &c, &n);

        median_tracker t;
        t.insert(1);

        long long ans = 1;
        for (int i = 2 ;i <= n ;i++) {
            int v = add(add(mul(t.get_mid() , a) , mul(b , i)) , c);
            ans += v;
            t.insert(v);
        }

        printf("%lld\n" , ans);
    }
}