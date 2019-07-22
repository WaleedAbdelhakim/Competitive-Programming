#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5 + 5;
vector<int> adj[N];

struct segtree {
    vector<int> arr , tree;

    void update (int i , int v , int l , int r , int pos) {
        if (i > r || i < l)
            return;
        if (l == r) {
            tree[pos] += v;
            return;
        }
        int mid = (l + r) / 2;
        update(i , v , l , mid , pos * 2);
        update(i , v , mid + 1 , r , pos * 2 + 1);
        tree[pos] = max(tree[pos * 2] , tree[pos * 2 + 1]);
    }

    int query(int s , int e , int l , int r , int pos) {
        if (l > e || r < s)
            return -1e9;
        if (l >= s && r <= e)
            return tree[pos];
        int mid = (l + r) / 2;
        return max(query(s , e , l , mid , pos * 2) , query(s , e , mid + 1 , r , pos * 2 + 1));
    }

    void update(int i , int v) {
        update(i , v , 0 , arr.size() - 1 , 1);
    }

    int query(int s , int e) {
        return query(s , e , 0 , arr.size() - 1 , 1);
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
    segtree st;

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
        st.arr = arr;
        st.tree = vector<int>(arr.size() * 4 , 0);
    }

    void update(int u , int v) {
        st.update(pos[u] , v);
    }

    int query(int a , int b) {
        int mx = 0;
        while (head[a] != head[b]) {
            if (dep[head[a]] < dep[head[b]])
                swap(a , b);
            mx = max(mx , st.query(pos[head[a]] , pos[a]));
            a = par[head[a]];
        }
        return max(mx , st.query(min(pos[a] , pos[b]) , max(pos[a] , pos[b])));
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int n , u , v;
    scanf("%d" , &n);
    for (int i = 0 ;i < n - 1 ;i++) {
        scanf("%d%d" , &u , &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    HeavyLight HLD(1);

    int q;
    scanf("%d" , &q);
    char type;
    int a , b;
    while (q--) {
        scanf(" %c %d %d" , &type , &a , &b);
        if (type == 'I')
            HLD.update(a , b);
        else
            printf("%d\n" , HLD.query(a , b));
    }
}
