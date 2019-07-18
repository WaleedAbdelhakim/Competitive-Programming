#include <bits/stdc++.h>

using namespace std;

struct edge {
    int to , cost , ind;
};

const int N = 1e5 + 5;
int vis[N] , p[N] , sz;
vector<edge> adj[N];

bool cycle(int node , int k) {
    if (vis[node])
        return vis[node] == 1;

    vis[node] = 1;
    for (auto c : adj[node])
        if (c.cost > k && cycle(c.to , k))
            return 1;
    vis[node] = 2;

    return 0;
}

void topo(int node , int k) {
    vis[node] = 1;
    for (auto c : adj[node])
        if (c.cost > k && !vis[c.to])
            topo(c.to , k);
    p[node] = sz++;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int n , m , u , v , c;
    scanf("%d%d" , &n , &m);
    for (int i = 1 ;i <= m ;i++) {
        scanf("%d%d%d" , &u , &v , &c);
        adj[u].push_back({v , c , i});
    }

    int l = 0 , r = 1e9 , k = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        memset(vis , 0 , sizeof vis);
        bool good = 1;
        for (int i = 1 ; good && i <= n ;i++)
            good &= vis[i] || !cycle(i , mid);

        if (good) {
            k = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    memset(vis , 0 , sizeof vis);
    for (int i = 1 ;i <= n ;i++)
        if (!vis[i])
            topo(i , k);

    vector<int> info;
    for (int i = 1 ;i <= n ;i++)
        for (auto c : adj[i])
            if (c.cost <= k && p[c.to] > p[i])
                info.push_back(c.ind);

    printf("%d %d\n" , k , info.size());
    for (int x : info)
        printf("%d " , x);
}