#include <bits/stdc++.h>

using namespace std;

const int N = 51, M = 1e5 + 5;
int s, d;
int memo[N][M];
bool good[N];
vector<pair<int, int> > adj[N];

int solve(int node, int rem) {
    if (node == d || rem <= 0)
        return !rem && node == d ? 0 : 1e9;
    int &ret = memo[node][rem];
    if (~ret)
        return ret;
    ret = 1e9;
    for (auto c : adj[node])
        if (good[c.first])
            ret = min(ret, solve(c.first, rem - c.second) + 1);
    return ret;
}

bool reach(int node , int par) {
    good[node] = 1;
    if (node == d)
        return 1;

    for (auto c : adj[node])
        if (c.first != par && reach(c.first , node))
            return 1;

    return good[node] = 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T, n, m;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &n, &m);

        for (int i = 1; i <= n; i++)
            adj[i].clear();

        int u, v, c, q;
        while (m--) {
            scanf("%d%d%d", &u, &v, &c);
            adj[u].push_back({v, c});
            adj[v].push_back({u, c});
        }

        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            scanf("%d%d%d", &s, &d, &c);
            memset(memo, -1, sizeof memo);
            memset(good, 0, sizeof good);
            reach(s , s);
            int ans = solve(s, c);
            if (ans >= (int) 1e9)
                puts("No");
            else
                printf("Yes %d\n", ans);
        }
        if (T) puts("");
    }
}