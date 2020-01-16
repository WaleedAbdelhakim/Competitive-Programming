#include <bits/stdc++.h>

using namespace std;

struct DSU{
    vector<int> par, size;
    int cc;
    DSU(int n) {
        cc = n;
        par.resize(n+1);
        size.assign(n+1, 1);
        iota(par.begin(), par.end(), 0);
    }
    int root(int a) {
        return par[a] == a ? a: par[a] = root(par[a]);
    }
    void unite(int a,int b) {
        a = root(a);
        b = root(b);
        if(a == b) return;
        if(size[a] < size[b]) swap(a,b);
        par[b] = a;
        size[a] += size[b];
        --cc;
    }
    bool same(int a,int b) {
        return root(a) == root(b);
    }
};

const int N = 1e4 + 5; // number of nodes
int vis[N] , low[N] , dfsTime[N] , comp_id[N] , Time;
vector<int> adj[N];
stack<int> st;
vector<vector<int> > comps;

int dfs(int node , int par) { // add par if undirected
    if(vis[node])
        return vis[node] == 1 ? low[node] : 1e9;

    dfsTime[node] = low[node] = Time++;
    vis[node] = 1;
    st.push(node);

    for (int child : adj[node]) // in case of undirected continue if par
        if (child != par)
            low[node] = min(low[node] , dfs(child , node));

    if(low[node] == dfsTime[node]) {
        comps.push_back(vector<int>());
        do {
            vis[st.top()] = 2;
            comp_id[st.top()] = comps.size() - 1;
            comps.back().push_back(st.top());
            st.pop();
        } while(comps.back().back() != node);
    }

    return low[node];
}



vector<int> dag[N]; // tree or dag
// zero based with number of nodes equal to comps.size()

void tarjan(int n) {
    for (int i = 1 ;i <= n ;i++) // one based
        if(!vis[i])
            dfs(i , i);
}

void init(int n) {
    fill(adj , adj + (n + 1) , vector<int>()); // n + 1 for one based
    fill(dag , dag + (n + 1) , vector<int>());
    memset(vis , 0 , (n + 1) * sizeof vis[0]);
    comps.clear();
}

int n , m , q;

void run_case() {
    init(n);

    while (m--) {
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    tarjan(n);

    DSU dsu(n);
    for (int i = 1 ;i <= n ;i++)
        for (int child : adj[i])
            if (comp_id[i] != comp_id[child])
                dsu.unite(i , child);

    while (q--) {
        int u , v;
        cin >> u >> v;
        cout << (dsu.same(u , v) ? "Y\n" : "N\n");
    }

    cout << "-\n";
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    while (cin >> n >> m >> q , n)
        run_case();
}