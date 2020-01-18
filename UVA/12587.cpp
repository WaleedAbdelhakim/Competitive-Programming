/*
    first of all, we only care about bridges     
    since other edges will have a maintaining cost = 0
    so we will compress each SCC in a node and connect these nodes with bridges
    the resulting graph will be a forest(set of trees)
    after that, we will binary search the answer in the range [max initial maintaining cost of a town, 1e18]
    and validate whether if we can give the responsibility of edges such 
    that max maintaining cost of a town <= current med
    we will do this using a greedy algorithm and we will do it for each tree in the forest
    let mn[u] = be the minimum maintaining cost of node u after giving the responsibility of every edge in its subtree
    so let's say you are currently at node u and now you want to calculate mn[u]
    mn[u] will be initially equal to the maintaining cost of node u
    and for each child v if mn[v] + cost[u][v] < mid the responsibility will be given to v
    otherwise, u will be responsible for it
*/

#include <bits/stdc++.h>

using namespace std;

struct edge {
    int to , cost;
};

const int N = 1e4 + 5; // number of nodes
int vis[N] , low[N] , dfsTime[N] , comp_id[N] , Time;
vector<edge> adj[N];
stack<int> st;
vector<vector<int> > comps;

int dfs(int node , int par) { // add par if undirected
    if(vis[node])
        return vis[node] == 1 ? low[node] : 1e9;

    dfsTime[node] = low[node] = Time++;
    vis[node] = 1;
    st.push(node);

    for (auto &c : adj[node]) // in case of undirected continue if par
        if (c.to != par)
            low[node] = min(low[node] , dfs(c.to , node));

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


vector<edge> dag[N]; // tree or dag
// zero based with number of nodes equal to comps.size()

vector<edge> bridge[N];

void tarjan(int n) {
    for (int i = 1 ;i <= n ;i++) // one based
        if(!vis[i])
            dfs(i , i);

    for (int i = 1 ;i <= n ;i++) { // one based
        for (auto &c : adj[i]) {
            if (comp_id[i] != comp_id[c.to]) {
                dag[comp_id[i]].push_back({comp_id[c.to], c.cost});
                bridge[i].push_back({c.to, c.cost});
            }
        }
    }
}

void init(int n) {
    fill(adj , adj + (n + 1) , vector<edge>()); // n + 1 for one based
    fill(dag , dag + (n + 1) , vector<edge>());
    fill(bridge , bridge + (n + 1) , vector<edge>());
    memset(vis , 0 , (n + 1) * sizeof vis[0]);
    comps.clear();
}

int c[N] , sz[N] , done[N] , vid;

long long dp[N];
int calc(int node) {
    done[node] = vid;
    sz[node] = comps[node].size();
    for (auto &c : dag[node])
        if (done[c.to] != vid)
            sz[node] += calc(c.to);
    return sz[node];
}

bool can(int node , int par , int cnt , long long mx) {
    for (auto &c : dag[node]) {
        if (c.to == par) continue;
        int up = cnt + sz[node] - sz[c.to];
        if (!can(c.to , node , up , mx))
            return 0;
    }

    for (int u : comps[node]) {
        dp[u] = c[u];
        for (auto &e : bridge[u]) {
            if (comp_id[e.to] == par) continue;
            int up = cnt + sz[node] - sz[comp_id[e.to]];
            if (dp[e.to] + up * 1ll * sz[comp_id[e.to]] * e.cost > mx)
                dp[u] += up * 1ll * sz[comp_id[e.to]] * e.cost;

            if (dp[u] > mx)
                return 0;
        }

    }

    return 1;
}

long long test_case() {
    int n , m;
    cin >> n >> m;
    for (int i = 1 ;i <= n ;i++)
        cin >> c[i];

    init(n);

    while (m--) {
        int u , v , c;
        cin >> u >> v >> c;
        adj[u].push_back({v , c});
        adj[v].push_back({u , c});
    }

    tarjan(n);

    ++vid;

    vector<int> roots;
    for (int i = 0 ;i < comps.size() ;i++) {
        if (done[i] == vid) continue;
        roots.push_back(i);
        calc(i);
    }

    long long l = *max_element(c + 1 , c + n + 1) , r = 1e18 , mnmax = -1;
    while (l <= r) {
        long long mid = (l + r) / 2;
        bool all_good = 1;
        for (int r : roots)
            all_good &= can(r , r , 0 , mid);

        if (all_good) {
            mnmax = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return mnmax;
}
int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int t;
    cin >> t;
    for (int test = 1 ; test <= t ; test++)
        cout << "Case " << test << ": " << test_case() << '\n';
}
