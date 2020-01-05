#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
map<long long , long long> k;
map<long long , vector<long long> > adj;

struct node {
    int sum = 0;
    node *zero, *one;
    node(int sum, node *zero, node *one) : sum(sum) , zero(zero) , one(one) {}
    node(int sum = 0) : sum(sum), one(this), zero(this) {}
};

node *insert(node *cur, int v , int i = 31) {
    if (i == 0)
        return new node(cur->sum + 1);

    node *zero = cur->zero;
    node *one = cur->one;

    int j = i - 1;
    if (v & (1 << j))
        one = insert(cur->one , v , j);
    else
        zero = insert(cur->zero , v , j);

    return new node(cur->sum + 1, zero, one);
}

map<long long , node*> roots;

int get_max(node *cur , int v , int i = 31) {
    if (i == 0)
        return 0;

    int j = i - 1;
    if (v & (1 << j)) {
        if (cur->zero->sum) return (1 << j) + get_max(cur->zero , v , j);
        return get_max(cur->one , v , j);
    }

    if (cur->one->sum) return (1 << j) + get_max(cur->one , v , j);
    return get_max(cur->zero , v , j);
}

int get_min(node *cur , int  v , int i = 31) {
    if (i == 0)
        return 0;

    int j = i - 1;
    if (v & (1 << j)) {
        if (cur->one->sum) return get_min(cur->one , v , j);
        return (1 << j) + get_min(cur->zero , v , j);
    }

    if (cur->zero->sum) return get_min(cur->zero , v , j);
    return (1 << j) + get_min(cur->one, v , j);
}

void dfs(int node , int par) {
    roots[node] = insert(roots[par] , k[node]);
    for (int child : adj[node])
        if (child != par)
            dfs(child , node);
}

int main() {
    ios::sync_with_stdio(0) ,  cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int  n , q , r ;
    cin >> n >> q >> r;
    cin >> k[r];

    int  u , v;
    for (int i = 0 ;i < n - 1 ;i++) {
        cin >> v >> u;
        cin >> k[v];
        adj[u].push_back(v);
    }

    roots[r] = new node();
    dfs(r , r);

    int last = 0 , type;
    while (q--) {
        cin >> type;
        type ^= last;
        if (type) {
            int u , val;
            cin >> u >> val;
            u ^= last;
            val ^= last;
            int mn = get_min(roots[u] , val);
            int mx = get_max(roots[u] , val);
            cout << mn << " " << mx << '\n';
            last = mn ^ mx;
        } else {
            int u , v;
            cin >> u >> v;
            u ^= last;
            v ^= last;

            cin >> k[v];
            k[v] ^= last;

            roots[v] = insert(roots[u] , k[v]);
        }
    }
}
