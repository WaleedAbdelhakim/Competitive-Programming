#include <bits/stdc++.h>

using namespace std;
#define pb push_back

int n, m;

struct node {
    int sum;
    bool lazy;
    node *left, *right;

    node(int sum = 0) : sum(sum), left(this), right(this), lazy(0) {}

    node(int sum, node *left, node *right) : sum(sum), left(left), right(right), lazy(0) {}

    node (node * a) : sum(a->sum) , left(a->left) , right(a->right) , lazy(a->lazy){}
};

void pushDown(node *nd, int l, int r) {
    if (nd->lazy) {
        nd->sum = (r - l + 1) - nd->sum;
        nd->left = new node(nd->left);
        nd->right = new node(nd->right);
        nd->left->lazy = !nd->left->lazy;
        nd->right->lazy = !nd->right->lazy;
    }
    nd->lazy = 0;
}

node *in(int val, node *cur, int l = 1, int r = n * m) {
    pushDown(cur, l, r);
    if (val > r || val < l)
        return cur;
    if (l == r)
        return new node(1);
    int mid = l + ((r - l) >> 1);
    node *left = in(val, cur->left, l, mid);
    node *right = in(val, cur->right, mid + 1, r);
    return new node(left->sum + right->sum, left, right);
}

node *del(int val, node *cur, int l = 1, int r = n * m) { // one based
    pushDown(cur, l, r);
    if (val > r || val < l)
        return cur;
    if (l == r)
        return new node(0);
    int mid = l + ((r - l) >> 1);
    node *left = del(val, cur->left, l, mid);
    node *right = del(val, cur->right, mid + 1, r);
    return new node(left->sum + right->sum, left, right);
}

node *updateRange(int s, int e, node *cur, int l = 1, int r = n * m) {
    pushDown(cur, l, r);
    if (l > e || r < s)
        return cur;
    if (l >= s && r <= e) {
        node *left = new node(cur->left);
        node *right = new node(cur->right);
        left->lazy = !left->lazy;
        right->lazy = !right->lazy;
        return new node((r - l + 1) - cur->sum , left , right);
    }

    int mid = l + ((r - l) >> 1);
    node *left = updateRange(s, e, cur->left, l, mid);
    node *right = updateRange(s, e, cur->right, mid + 1, r);
    return new node(left->sum + right->sum, left, right);
}


int getPos(int i, int j) {
    return (i - 1) * m + j;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int q;
    scanf("%d%d%d", &n, &m, &q);
    vector<node*> root = {new node};

    int type, i, j, k;
    while (q--) {
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d%d", &i, &j);
            root.pb(in(getPos(i, j), root.back()));
        } else if (type == 2) {
            scanf("%d%d", &i, &j);
            root.pb(del(getPos(i, j), root.back()));
        } else if (type == 3) {
            scanf("%d", &i);
            root.pb(updateRange(getPos(i, 1), getPos(i, 1) + m - 1, root.back()));
        } else {
            scanf("%d", &k);
            root.pb(root[k]);
        }
        printf("%d\n", root.back()->sum);
    }
}