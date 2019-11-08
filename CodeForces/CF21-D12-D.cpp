#include <bits/stdc++.h>

using namespace std;

const int N = 16;
int n;
vector<int> adj[N];
int d[N][N] , memo[1 << N];
bool vis[N];

void dfs(int node) {
    vis[node] = 1;
    for (int child : adj[node])
        if (!vis[child])
            dfs(child);
}

int solve (int msk) {
    if (!msk)
        return 0;

    int &ret = memo[msk];
    if (~ret)
        return ret;

    ret = 1e9;

    int f;
    for (int i = n - 1 ;i >= 0 ;i--)
        if (msk & (1 << i))
            f = i;

    for (int i = f + 1 ;i < n ;i++)
        if (msk & (1 << i))
            ret = min(ret , solve(msk ^ (1 << i) ^ (1 << f)) + d[i][f]);

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int m , u , v , w , sum = 0;
    scanf("%d%d" , &n , &m);

    memset(d , '?' , sizeof d);
    while (m--) {
        scanf("%d%d%d" , &u , &v , &w);
        sum += w;
        u-- , v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        d[u][v] = min(d[u][v] , w);
        d[v][u] = min(d[v][u] , w);
    }

    for (int i = 0 ; i < n ;i++)
        d[i][i] = 0;

    for (int k = 0 ;k < n ;k++)
        for (int i = 0 ;i < n ;i++)
            for (int j = 0 ;j < n ;j++)
                d[i][j] = min(d[i][j] , d[i][k] + d[k][j]);

    dfs(0);
    for (int i = 0 ;i < n ;i++) {
        if (adj[i].size() && !vis[i]) {
            puts("-1");
            return 0;
        }
    }

    int msk = 0;
    for (int i = 0 ;i < n ;i++)
        if (adj[i].size()&1)
            msk |= 1 << i;

    memset(memo , -1 , sizeof memo);
    printf("%d" , sum + solve(msk));
}