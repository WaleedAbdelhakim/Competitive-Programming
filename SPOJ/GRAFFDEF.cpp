#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int n , m;
int vis[N] , low[N] , dfsTime[N] , Time;
vector<int> adj[N] , tree[N];
stack<int> st;
vector<vector<int> > comps;
int c[N] , sz[N];

int dfs(int node , int par) {
    if(vis[node])
        return vis[node] == 1 ? low[node] : 1e9; // return low[node] if visited and in the same SCC , black / gray = gray

    dfsTime[node] = low[node] = Time++;
    vis[node] = 1;
    st.push(node);

    for (int child : adj[node])
        if (child != par)
            low[node] = min(low[node] , dfs(child , node));

    if(low[node] == dfsTime[node]) { // the root of the SCC
        comps.push_back(vector<int>());
        do {
            vis[st.top()] = 2;     // we mark all the nodes of the current SCC as black
            comps.back().push_back(st.top());
            st.pop();
        } while(comps.back().back() != node);
    }

    return low[node];
}

void tarjan() {
    for (int i = 1 ;i <= n ;i++)
        if(!vis[i])
            dfs(i , i);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    scanf("%d%d" , &n , &m);

    int u , v;
    for (int i = 0 ;i < m ;i++) {
        scanf("%d%d" , &u , &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    tarjan();

    long long cnt = 0 , before = 0;
    for (auto &v : comps) {
        cnt += v.size() * 1ll * before;
        before += v.size();
    }
    printf("%.5f" , 2 * cnt / (n * (n - 1.0)));
}