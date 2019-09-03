#include <bits/stdc++.h>

using namespace std;

const int N = 1505 , M = 3e5 + 5;
long long sum[N][N], square[N][N], cnt[N][N];
int alone[M];

int add(long long a[N][N], int lr, int rr, int lc, int rc, long long x) {
    a[lr][lc] += x;
    a[rr + 1][rc + 1] += x;
    a[lr][rc + 1] += -x;
    a[rr + 1][lc] += -x;
}

void acom(long long a[N][N], int i, int j) {
    a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
}

pair<int, int> Quadratic_Formula(long long a, long long b, long long c) {
    long long sqt = sqrt(b * b - 4 * a * c);
    return {(-b + sqt) / (2 * a), (-b - sqt) / (2 * a)};
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T, n, m;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);

        memset(alone, 0, (n + 1) * sizeof alone[0]);
        for (int i = 1 ;i <= m ;i++)
            for (int j = 1 ;j <= m ;j++)
                sum[i][j] = square[i][j] = cnt[i][j] = 0;

        int lr, rr, lc, rc;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d%d", &lr, &rr, &lc, &rc);
            add(sum, lr, rr, lc, rc, i);
            add(square, lr, rr, lc, rc, i * 1ll * i);
            add(cnt, lr, rr, lc, rc, 1);
        }

        int covered = 0;
        map<pair<int, int>, int> info;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                acom(sum, i, j);
                acom(square, i, j);
                acom(cnt, i, j);
                covered += cnt[i][j] != 0;
                if (cnt[i][j] == 1) {
                    alone[sum[i][j]]++;
                } else if (cnt[i][j] == 2) {
                    long long a = 2, b = -2 * sum[i][j], c = sum[i][j] * sum[i][j] - square[i][j];
                    info[Quadratic_Formula(a, b, c)]++;
                }
            }
        }

        int mx[3] = {0 , 0 , 0};
        for (int i = 1; i <= n; i++) {
            mx[0] = alone[i];
            sort(mx , mx + 3);
        }

        int ans = covered - mx[2] - mx[1];
        for (auto &p : info)
            ans = min(ans, covered - alone[p.first.first] - alone[p.first.second] - p.second);

        printf("%d\n", ans);
    }
}