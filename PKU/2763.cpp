#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct edge {
    int to , cost , ind;
    edge (int _to , int _cost , int _ind) : to(_to) , cost(_cost) , ind(_ind) {}
};

const int N = 1e5 + 5; // number of nodes
vector<edge> adj[N];
int val[N] , on[N];

struct BIT {
    vector<int> tree;
    BIT(int n) : tree(n + 2){}

    void upd(int p , int v) {
        for (int i = ++p ;i < tree.size() ; i += i & -i)
            tree[i] += v;
    }

    int get(int p) {
        int sum = 0;
        for (int i = ++p; i ; i -= i & -i)
            sum += tree[i];
        return sum;
    }

    int query(int l , int r) {
        if (r < l) return 0;
        return get(r) - get(l - 1);
    }
};

class HeavyLight {
    int hvy[N] , par[N] , dep[N] , head[N] , pos[N];
    // pos : pos of every node in the array of chains
    // dep : depth of every node
    // hvy : the hvy child of every node -1 if leaf
    // par : parent of every node -1 if root
    // head : head of chain of the ith node

    vector<int> arr;
    BIT *st;

    int dfs(int u) {
        int sz = 0 , mx = -1 ;
        hvy[u] = -1;
        for (int i = 0 ;i < adj[u].size() ;i++) {
            edge &c = adj[u][i];
            if (c.to != par[u]) {
                par[c.to] = u;
                dep[c.to] = dep[u] + 1;
                int v_size = dfs(c.to);
                if (v_size > mx) {
                    mx = v_size;
                    hvy[u] = c.to;
                }
                sz += v_size;
            }
        }
        return sz;
    }

    void build_chains(int u) {
        head[u] = par[u] != -1 && hvy[par[u]] == u ? head[par[u]] : u;

        pos[u] = arr.size();
        arr.push_back(val[u]);

        if (hvy[u] != -1)
            build_chains(hvy[u]);

        for (int i = 0 ;i < adj[u].size() ;i++) {
            edge &c = adj[u][i];
            if (c.to != par[u] && c.to != hvy[u])
                build_chains(c.to);
        }
    }

public:
    HeavyLight (int root) {
        par[root] = -1;
        dep[root] = 0;
        dfs(root);
        build_chains(root);

        st = new BIT(arr.size());
        for (int i = 0 ;i < arr.size() ;i++)
            st->upd(i , arr[i]);
    }

    void update(int node , int v) {
        st->upd(pos[node] , v - val[node]);
        val[node] = v;
    }

    long long query(int a , int b) {
        long long sum = 0;
        while (head[a] != head[b]) {
            if (dep[head[a]] < dep[head[b]])
                swap(a , b);
            sum += st->query(pos[head[a]] , pos[a]);
            a = par[head[a]];
        }
        return sum + st->query(min(pos[a] , pos[b]) + 1  , max(pos[a] , pos[b])); // min + 1 to ignore the lca
    }
};

void dfs(int node , int par) {
    for (int i = 0 ;i < adj[node].size() ;i++) {
        edge &c = adj[node][i];
        if (c.to == par) continue;
        val[c.to] = c.cost;
        on[c.ind] = c.to;
        dfs(c.to, node);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int n , q , s;
    scanf("%d%d%d" , &n , &q , &s);

    int u , v , w;
    for (int i = 0 ;i < n - 1 ;i++) {
        scanf("%d%d%d" , &u , &v , &w);
        adj[u].push_back(edge(v , w , i + 1));
        adj[v].push_back(edge(u , w , i + 1));
    }

    dfs(1 , 1);
    HeavyLight HLD(1);

    int type;
    while (q--) {
        scanf("%d" , &type);
        if (type) {
            int i , nw;
            scanf("%d%d",&i,&nw);
            HLD.update(on[i] , nw);
        } else {
            int v;
            scanf("%d",&v);
            printf("%d\n" , HLD.query(s , v));
            s = v;
        }
    }
}