#include <bits/stdc++.h>

//#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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

#define node first
#define cost second

const int N = 1005;
int n , m;
vector<pair<int , int> > adj[N];
set<int> info;
vi ans;
int dist[N];
int vis[N] , vid;
void bellman() {
    memset(dist , 0 , sizeof dist);
    for (int it = 0 ;it < n ;it++) {
        for (int i = 0 ;i < n ;i++) {
            for (auto &c : adj[i])
                if(dist[c.node] > dist[i] + c.cost) {
                    dist[c.node] = dist[i] + c.cost;
                    if(it == n - 1)
                        info.insert(i);
                }
        }
    }
}

void dfs(int node) {
    vis[node] = vid;
    ans.pb(node);
    for (auto &c : adj[node])
        if(vis[c.node] != vid)
            dfs(c.node);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    int T;
    scanf("%d",&T);

    for (int test = 1 ; test <= T ;test++) {
        scanf("%d%d",&n,&m);

        for (int i = 0 ;i < N ;i++)
            adj[i].clear();

        int a , b , c;
        while(m--) {
            scanf("%d%d%d",&a,&b,&c);
            adj[b].pb({a , c});
        }

        info.clear();
        ans.clear();
        vid++;
        bellman();
        for (int x : info)
            if(vis[x] != vid)
                dfs(x);
        sort(all(ans));

        printf("Case %d: " , test);
        if(!ans.size())
            puts("impossible");
        else {
            for (int i = 0 ;i < ans.size() ;i++)
                printf("%d%c" , ans[i] , " \n"[i == ans.size() - 1]);
        }
    }
}