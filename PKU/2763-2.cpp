#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5 + 5, M = 18; // update according to the problem

struct edge {
    int to , cost , id;
    edge(int _to , int _cost , int _id) : to(_to) , cost(_cost) , id(_id) {}
};


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

} bit(2 * N);

vector<edge> adj[N];
int occ[N], E[2 * N], L[2 * N], table[M][2 * N], LG[2 * N], sz , nxt;
int in[2 * N] , out[2 * N] , on[N];

void dfs(int node = 0, int par = -1, int level = 0) {
    table[0][sz] = sz;
    occ[node] = sz;
    E[sz] = node;
    L[sz++] = level;
    in[node] = nxt++;
    for (int i = 0 ;i < adj[node].size() ;i++) {
        edge &c = adj[node][i];
        if (c.to == par) continue;
        on[c.id] = c.to;
        dfs(c.to , node, level + 1);
        E[sz] = node;
        table[0][sz] = sz;
        L[sz++] = level;
    }
    out[node] = nxt++;
}

void build() {
    sz = 0;
    dfs();

    for (int j = 1; j <= M; j++) {
        for (int i = 0; i + (1 << j) - 1 < sz; i++) {
            int f = table[j - 1][i];
            int s = table[j - 1][i + (1 << (j - 1))];
            table[j][i] = L[f] < L[s] ? f : s;
        }
    }
}

int RMQ(int l, int r) {
    if (r < l)
        swap(l, r);
    int lg = LG[r - l + 1];
    int f = table[lg][l];
    int s = table[lg][r - (1 << lg) + 1];
    return L[f] < L[s] ? E[f] : E[s];
}

int LCA(int a, int b) {
    return RMQ(occ[a], occ[b]);
}

void init() {
    LG[0] = -1;
    for (int i = 1; i < 2 * N; i++)
        LG[i] = LG[i - 1] + !(i - (i & (-i)));
}

int query(int u , int v) {
    int lca = LCA(u , v);
    return bit.get(in[u]) + bit.get(in[v]) - 2 * bit.get(in[lca]);
}

int ec[N];

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int n , q , s;
    scanf("%d%d%d" , &n , &q , &s);

    int u , v;
    for (int i = 0 ;i < n - 1 ;i++) {
        scanf("%d%d%d" , &u , &v , ec + i);
        u-- , v--;
        adj[u].push_back(edge(v , ec[i] , i));
        adj[v].push_back(edge(u , ec[i] , i));
    }

    init();
    build();

    for (int i = 0 ;i < n ;i++) {
        for (int j = 0 ;j < adj[i].size() ;j++) {
            int u = i , v = adj[i][j].to;
            if (L[occ[u]] > L[occ[v]]) continue;
            bit.upd(in[v] , adj[i][j].cost);
            bit.upd(out[v] , -adj[i][j].cost);
        }
    }

    int type;
    while (q--) {
        scanf("%d" , &type);
        if (type) {
            int i , w;
            scanf("%d%d" , &i , &w);
            i--;
            bit.upd(in[on[i]] , w - ec[i]);
            bit.upd(out[on[i]] , ec[i] - w);
            ec[i] = w;
        } else {
            int to;
            scanf("%d" , &to);
            printf("%d\n" , query(s - 1 , to - 1));
            s = to;
        }
    }
}
