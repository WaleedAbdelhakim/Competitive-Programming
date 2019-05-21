#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
int n;
double memo[N][2] , vis[N][2] , vid;
char a[N] , b[N];

double solve (int rem , bool joker) {
    if (!rem)
        return !joker;

    double &ret = memo[rem][joker];
    if (vis[rem][joker] == vid)
        return ret;

    vis[rem][joker] = vid;

    ret = (rem / (0.0 + rem + !joker)) * (1 - solve(rem - 1 , !joker));
    if (joker)
        return ret;

    double p = 1.0 / (rem + 1);
    ret += solve(rem - 1 , 1) * p * (1 - p);

    return ret = ret / (1 - p * p);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int T;
    scanf("%d" , &T);
    while (T--) {
        scanf("%d%s%s" , &n , a , b);
        int cnt = 0;
        bool joker = 0;
        for (int i = 0 ;i < n ;i++) {
            cnt += a[i] == '1' && b[i] == '1';
            joker |= a[i] == '1' && b[i] == '0';
        }

        ++vid;
        printf("%.9f\n" , solve(cnt , joker));
    }
}