#include <bits/stdc++.h>

using namespace std;

const int N = 9e3 + 5;
int n , m;
int vis[N] , low[N] , dfsTime[N] , Time;
vector<int> adj[N];
stack<int> st;
vector<vector<int> > comps;
int comp[N];

int dfs(int node) {
    if(vis[node])
        return vis[node] == 1 ? low[node] : 1e9;

    dfsTime[node] = low[node] = Time++;
    vis[node] = 1;
    st.push(node);

    for (int child : adj[node])
        low[node] = min(low[node] , dfs(child));

    if(low[node] == dfsTime[node]) {
        comps.push_back(vector<int>());
        do {
            vis[st.top()] = 2;
            comp[st.top()] = comps.size() - 1;
            comps.back().push_back(st.top());
            st.pop();
        } while(comps.back().back() != node);
    }

    return low[node];
}

vector<int> tree[N];

void tarjan() {
    for (int i = 1 ;i <= n ;i++)
        if(!vis[i])
            dfs(i);

    for (int i = 1 ;i <= n ;i++)
        for (int child : adj[i])
            if (comp[i] != comp[child])
                tree[comp[i]].push_back(comp[child]);
}

int vis2[N] , vid;
int solve (int node) {
    vis2[node] = vid;
    int ret = comps[node].size();
    for (int child : tree[node])
        if (vis2[child] != vid)
            ret += solve(child);
    return ret;
}

void init() {
    fill(adj , adj + (n + 1) , vector<int>());
    fill(tree , tree + (n + 1) , vector<int>());
    comps.clear();
    memset(vis , 0 , (n + 1) * sizeof vis[0]);
    memset(low  , 0 , (n + 1) * sizeof low[0]);
    memset(dfsTime , 0 , (n + 1) * sizeof dfsTime[0]);
    Time = 1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r"  ,stdin);
#endif
    int t , m;
    scanf("%d" , &t);
    while (t--) {
        scanf("%d%d",  &n , &m);
        init();

        int a , b;
        while (m--) {
            scanf("%d%d" , &a , &b);
            adj[b].push_back(a);
        }

        tarjan();

        int mx = 0;
        vector<int> best;

        for (int i = 0 ;i < comps.size() ;i++) {
            ++vid;
            int cnt = solve(i);
            if (cnt > mx) {
                mx = cnt;
                best = {i};
            } else if (cnt == mx) {
                best.push_back(i);
            }
        }
        vector<int> ans;
        for (int c : best)
            for (int x : comps[c])
                ans.push_back(x);

        sort(ans.begin() , ans.end());

        for (int i = 0 ;i < ans.size() ;i++)
            printf("%d%c" , ans[i] , " \n"[i == ans.size() - 1]);
    }
}