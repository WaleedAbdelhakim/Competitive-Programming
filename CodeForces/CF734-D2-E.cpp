#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
vector<int> adj[N], adj2[N];
int vis[N], col[N], comp[N], cur;

void dfs(int node) {
    comp[node] = cur;
    vis[node] = 1;
    for (int child : adj[node])
        if (!vis[child] && col[child] == col[node])
            dfs(child);
}

pair<int, int> get_diameter(int node, int par = -1) {
    int d = 0, mx[3] = {};
    for (auto child : adj2[node]) {
        if (child == par) continue;
        auto p = get_diameter(child, node);
        mx[0] = p.second;
        sort(mx, mx + 3);
        d = max(d, p.first);
    }
    return {max(d, mx[2] + mx[1] + 1), mx[2] + 1};
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int n, u, v;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", col + i);

    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs(i) , cur++;

    for (int i = 1 ;i <= n ;i++)
        for (int c : adj[i])
            if (comp[i] != comp[c])
                adj2[comp[i]].push_back(comp[c]);

    printf("%d", get_diameter(1).first / 2);
}