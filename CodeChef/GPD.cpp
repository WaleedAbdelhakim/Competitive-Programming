#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
map<long long , long long> k;
map<long long , vector<long long> > adj;

struct node {
    long long sum = 0;
    node *left, *right;
    node(long long sum, node *left, node *right) : sum(sum), left(left), right(right) {}
    node(long long sum = 0) : sum(sum), left(this), right(this) {}
};

node *insert(node *cur, long long v , long long i = 31) {
    if (i == 0)
        return new node(cur->sum + 1);

    node *left = cur->left;
    node *right = cur->right;

    long long j = i - 1;
    if (v & (1ll << j))
        left = insert(cur->left , v , j);
    else
        right = insert(cur->right , v , j);

    return new node(cur->sum + 1, left, right);
}

map<long long , node*> roots;

long long get_max(node *cur , long long v , long long i = 31) {
    if (i == 0)
        return 0;

    long long j = i - 1;
    if (v & (1ll << j)) {
        if (cur->right->sum) return (1ll << j) + get_max(cur->right , v , j);
        return get_max(cur->left , v , j);
    }

    if (cur->left->sum) return (1ll << j) + get_max(cur->left , v , j);
    return get_max(cur->right , v , j);
}

long long get_min(node *cur , long long v , long long i = 31) {
    if (i == 0)
        return 0;

    long long j = i - 1;
    if (v & (1ll << j)) {
        if (cur->left->sum) return get_min(cur->left , v , j);
        return (1ll << j) + get_min(cur->right , v , j);
    }

    if (cur->right->sum) return get_min(cur->right , v , j);
    return (1ll << j) + get_min(cur->left, v , j);
}

void dfs(long long node , long long par) {
    roots[node] = insert(roots[par] , k[node]);
    for (long long child : adj[node])
        if (child != par)
            dfs(child , node);
}

int main() {
    ios::sync_with_stdio(0) ,  cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    long long n , q , r ;
    cin >> n >> q >> r;
    cin >> k[r];

    long long u , v;
    for (long long i = 0 ;i < n - 1 ;i++) {
        cin >> v >> u;
        cin >> k[v];
        adj[u].push_back(v);
    }

    roots[r] = new node();
    dfs(r , r);

    long long last = 0 ;
    long long type;
    while (q--) {
        cin >> type;
        type ^= last;
        if (type) {
            long long u , val;
            cin >> u >> val;
            u ^= last;
            val ^= last;
            long long mn = get_min(roots[u] , val);
            long long mx = get_max(roots[u] , val);
            cout << mn << " " << mx << '\n';
            last = mn ^ mx;
        } else {
            long long u , v;
            cin >> u >> v;
            u ^= last;
            v ^= last;

            cin >> k[v];
            k[v] ^= last;

            roots[v] = insert(roots[u] , k[v]);
        }
    }
}