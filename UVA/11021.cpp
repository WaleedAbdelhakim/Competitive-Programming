#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
int n, k, m;
double p[N], dp[N];

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d%d%d", &n, &k, &m);
        for (int i = 0; i < n; i++)
            scanf("%lf" , &p[i]);

        dp[m] = 0;
        for (int i = m - 1; i >= 0; i--) {
            dp[i] = p[0];
            double prob = dp[i + 1];
            for (int j = 1; j < n; j++) {
                dp[i] += p[j] * prob;
                prob *= dp[i + 1];
            }
        }

        double ans = 1;
        for (int i = 0; i < k; i++)
            ans *= dp[0];

        printf("Case #%d: %.7f\n", t, ans);
    }
}