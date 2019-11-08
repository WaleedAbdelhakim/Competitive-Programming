#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5; // number of nodes
vector<int> adj[N];
int val[N]; // number on nodes

class segtree {
    struct node {
        long long v = 0; // default value for the leafs
        int lazy = 0; // no lazy value

        inline void apply(int l, int r , int x) {
            v += x * (r - l + 1ll);
            // set v to the new value of range [l , r] when updated with x
        }

        inline void add_lazy(int x) {
            lazy += x;
            // lazy combine
        }

        inline node operator +(const node &other) const {
            node ret;
            ret.v = v + other.v;
            // combine v with other.v
            return ret;
        }

        inline bool isLazy() {return lazy != 0;}
        inline void cancel() {lazy = 0;}
    };

    inline void push(int l, int r, int p) {
        if (tree[p].isLazy()) {
            tree[p].apply(l, r, tree[p].lazy);
            if (l != r) {
                tree[left(p)].add_lazy(tree[p].lazy);
                tree[right(p)].add_lazy(tree[p].lazy);
            }
            tree[p].cancel();
        }
    }

    inline int left(int p) { return p << 1; }
    inline int right(int p) { return (p << 1) + 1; }

    int n;
    vector<node> tree;

    void build(int l, int r, int p, const vector<int> &v) {
        if (l == r) {
            tree[p].v = v[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, left(p), v);
        build(mid + 1, r, right(p), v);
        tree[p] = tree[left(p)] + tree[right(p)];
    }

    void update(int s, int e , int l, int r, int p) {
        push(l, r, p);
        if (l > e || r < s)
            return;
        if (l >= s && r <= e) {
            tree[p].apply(l, r , 1);
            if (l != r) {
                tree[left(p)].add_lazy(1);
                tree[right(p)].add_lazy(1);
            }
            return;
        }
        int mid = (l + r) >> 1;
        update(s, e , l, mid, left(p));
        update(s, e , mid + 1, r, right(p));
        tree[p] = tree[left(p)] + tree[right(p)];
    }

    node query(int s , int e , int l , int r , int p) {
        push(l , r , p);
        if (l >= s && r <= e) return tree[p];
        int mid = (l + r) >> 1;
        if (e <= mid)
            return query(s , e , l , mid , left(p));
        else if (s > mid)
            return query(s , e , mid + 1 , r , right(p));
        return query(s , e , l , mid , left(p)) + query(s , e , mid + 1 , r , right(p));
    }

public:
    segtree(int _n) : n(_n) {tree.resize(4 * n);}
    segtree(const vector<int> &v) : n(v.size()) {
        tree.resize(4 * n);
        build(0, n - 1, 1, v);
    }

    void update(int s, int e) {
        if (e < s) return;
        update(s, e,0, n - 1, 1);
    }

    long long query(int s, int e) {
        if (e < s) return 0;
        return query(s, e, 0, n - 1, 1).v;
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
    segtree *st;

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

        pos[u] = arr.size();
        arr.push_back(val[u]);

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
        st = new segtree(arr);
    }

    void update(int a , int b) {
        while (head[a] != head[b]) {
            if (dep[head[a]] < dep[head[b]])
                swap(a , b);
            st->update(pos[head[a]] , pos[a]);
            a = par[head[a]];
        }
        st->update(min(pos[a] , pos[b]) + 1 , max(pos[a] , pos[b]));
    }

    long long query(int a , int b) {
        long long sum = 0;
        while (head[a] != head[b]) {
            if (dep[head[a]] < dep[head[b]])
                swap(a , b);
            sum += st->query(pos[head[a]] , pos[a]);
            a = par[head[a]];
        }
        return sum + st->query(min(pos[a] , pos[b]) + 1 , max(pos[a] , pos[b]));
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int n , m , u , v;
    scanf("%d%d" , &n , &m);
    for (int i = 0 ;i < n - 1 ;i++) {
        scanf("%d%d" , &u , &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }


    HeavyLight HLD(1);

    char type;
    while (m--) {
        scanf(" %c%d%d" , &type , &u , &v);
        if (type == 'P')
            HLD.update(u , v);
        else
            printf("%lld\n" , HLD.query(u , v));
    }
}