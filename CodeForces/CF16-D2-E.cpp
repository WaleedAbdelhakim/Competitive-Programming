#include <bits/stdc++.h>

using namespace std;

#define ones(n) __builtin_popcount(n)

const int N = 19;
int n;
double win[N][N] , memo[1 << N];

double solve (int msk) {
    if (msk == (1 << n) - 1)
        return 1;

    double &ret = memo[msk];
    if (ret == ret)
        return ret;


    ret = 0;
    int alive = ones(msk);
    double p = 2.0 / (alive * alive + alive);
    for (int i = 0 ;i < n ;i++) {
        if (!((1 << i)&msk)) continue;
        for (int j = 0 ;j < n ;j++) {
            if (msk & (1 << j)) continue;
            ret += p * win[i][j] * solve(msk | (1 << j));
        }
    }
    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    scanf("%d" , &n);
    for (int i = 0 ;i < n ;i++)
        for (int j = 0 ;j < n;j++)
            scanf("%lf" , &win[i][j]);

    memset(memo , -1 , sizeof memo);
    for (int i = 0 ;i < n ;i++)
        printf("%.7f " , solve(1 << i));
}