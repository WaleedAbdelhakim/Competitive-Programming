#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5; // number of nodes
int hvy[N] , par[N] , dep[N] , head[N] , pos[N] , node[N];
vector<int> adj[N];

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

    int sum(int l , int r) {
        return get(r) - get(l - 1);
    }

    int first_in_range(int l , int r) {
        int pos = 0 , s = 0 , k = get(l - 1) + 1;
        for (int i = 1 + log2(tree.size()) ;i >= 0 ;i--)
            if (pos + (1 << i) < tree.size() && s + tree[pos + (1 << i)] < k)
                s += tree[pos + (1 << i)] , pos += (1 << i);
        return pos;
    }
} bit(N);

class HeavyLight {
    vector<int> arr;

    int dfs(int u) {
        int sz = 0 , mx = -1 ;
        hvy[u] = -1;
        for (int v : adj[u]) {
            if (v != par[u]) {
                par[v] = u;
                dep[v] = dep[u] + 1;
                int v_size = dfs(v);
                if (v_size > mx) {
                    mx = v_size;
                    hvy[u] = v;
                }
                sz += v_size;
            }
        }
        return sz;
    }

    void build_chains(int u) {
        head[u] = par[u] != -1 && hvy[par[u]] == u ? head[par[u]] : u;

        node[arr.size()] = u;
        pos[u] = arr.size();
        arr.push_back(0);

        if (hvy[u] != -1)
            build_chains(hvy[u]);

        for (int v : adj[u])
            if (v != par[u] && v != hvy[u])
                build_chains(v);
    }

public:
    HeavyLight (int root) {
        par[root] = -1;
        dep[root] = 0;
        dfs(root);
        build_chains(root);
    }

    void update(int node) {
        if (bit.sum(pos[node] , pos[node]))
            bit.upd(pos[node] , -1);
        else
            bit.upd(pos[node] , 1);
    }

    int query(int a , int b) {
        int s = 0;
        vector<pair<int , int> > v[2];
        while (head[a] != head[b]) {
            if (dep[head[a]] < dep[head[b]]) {
                swap(a , b);
                s = !s;
            }

            if (!s)
                v[0].push_back({pos[head[a]] , pos[a]});
            else
                v[1].push_back({pos[head[a]] , pos[a]});

            a = par[head[a]];
        }

        v[0].push_back({min(pos[a] , pos[b]) , max(pos[a] , pos[b])});
        for (auto &p : v[0])
            if (bit.sum(p.first , p.second))
                return node[bit.first_in_range(p.first , p.second)];

        for (int i = v[1].size() - 1 ;i >= 0 ;i--)
            if (bit.sum(v[1][i].first , v[1][i].second))
                return node[bit.first_in_range(v[1][i].first , v[1][i].second)];

        return -1;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int n , q , u , v;
    scanf("%d%d" , &n , &q);
    for (int i = 0 ;i < n - 1 ;i++) {
        scanf("%d%d" , &u , &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    HeavyLight hld(1);

    int type;
    while (q--) {
        scanf("%d%d" , &type , &u);
        if (type)
            printf("%d\n" , hld.query(1 , u));
        else
            hld.update(u);
    }
}

