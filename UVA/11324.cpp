#include <bits/stdc++.h>

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

//template<typename T>
//using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef vector<int> vi;
typedef long long ll;

#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
#define watch(x) cout << (#x) << " is " << (x) << endl

int di[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dj[] = {1, -1, 0, 0, -1, 1, 1, -1};

const int N = 1e3 + 5;
int n, m;
vi adj[N] , adj2[N];

vector<vi> components;
int low[N] , vis[N] , comp[N] , memo[N] , vis2[N] , Time , vid;
stack<int> s;

int dfs(int node) {
    if(vis[node])
        return vis[node] == 1 ? low[node] : inf;

    vis[node] = 1;
    int dfsTime = low[node] = Time++;
    s.push(node);

    for (int child : adj[node])
        low[node] = min(low[node] , dfs(child));


    if(dfsTime == low[node]) {
        components.pb(vi());
        do {
            components.back().pb(s.top());
            comp[s.top()] = components.size() - 1;
            vis[s.top()] = 2;
            s.pop();
        } while(components.back().back() != node);
    }

    return low[node];
}

void buildDag() {
    Time = 0;
    memset(vis , 0 , sizeof vis);
    components.clear();

    for (int i = 1 ;i <= n ;i++)
        if(!vis[i])
            dfs(i);

    for (int i = 1 ;i < N;i++)
        adj2[i].clear();

    for (int i = 1 ;i <= n ;i++)
        for (int child : adj[i])
            if(comp[i] != comp[child])
                adj2[comp[i]].pb(comp[child]);

}

int solve(int node) {
    int &ret = memo[node];
    if(vis2[node] == vid)
        return ret;

    vis2[node] = vid;
    ret = 0;

    for (int child : adj2[node])
        ret = max(ret , solve(child));

    ret += components[node].size();
    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);

        for (int i = 1 ; i < N; i++)
            adj[i].clear();

        int a, b;
        while (m--) {
            scanf("%d%d", &a, &b);
            adj[a].pb(b);
        }

        buildDag();

        vid++;

        int mx = 0;
        for (int i = 0 ;i < components.size() ;i++)
            mx = max(mx , solve(i));

        printf("%d\n" , mx);
    }
}