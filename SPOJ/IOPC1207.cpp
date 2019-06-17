#include <bits/stdc++.h>

using namespace std;


class segtree {
    struct node {
        int v = 0;
        int lazy = 0;

        inline void apply(int l, int r, int x) {
            if (x) v = (r - l + 1) - v;
        }

        inline void add_lazy(int x) {
            lazy ^= x;
        }

        inline node operator+(const node &other) const {
            node ret;
            ret.v = v + other.v;
            return ret;
        }

        inline bool isLazy() { return lazy;}

        inline void cancel() { lazy = 0; }
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

    void update(int s, int e, int v, int l, int r, int p) {
        push(l, r, p);
        if (l > e || r < s)
            return;
        if (l >= s && r <= e) {
            tree[p].apply(l, r, v);
            if (l != r) {
                tree[left(p)].add_lazy(v);
                tree[right(p)].add_lazy(v);
            }
            return;
        }
        int mid = (l + r) >> 1;
        update(s, e, v, l, mid, left(p));
        update(s, e, v, mid + 1, r, right(p));
        tree[p] = tree[left(p)] + tree[right(p)];
    }

    node query(int s, int e, int l, int r, int p) {
        push(l, r, p);
        if (l >= s && r <= e) return tree[p];
        int mid = (l + r) >> 1;
        if (e <= mid)
            return query(s, e, l, mid, left(p));
        else if (s > mid)
            return query(s, e, mid + 1, r, right(p));
        return query(s, e, l, mid, left(p)) + query(s, e, mid + 1, r, right(p));
    }

public:
    segtree(int _n ) : n(_n) { tree.resize(4 * n); }

    segtree(const vector<int> &v) : n(v.size()) {
        tree.resize(4 * n);
        build(0, n - 1, 1, v);
    }

    void update(int p, int v) {
        update(p, p, v, 0, n - 1, 1);
    }

    void update(int s, int e, int v) {
        update(s, e, v, 0, n - 1, 1);
    }

    int query(int p) {
        return query(p, p, 0, n - 1, 1).v;
    }

    int query(int s, int e) {
        return query(s, e, 0, n - 1, 1).v;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T, n , m , z , q;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &n, &m, &z, &q);

        segtree trees[3] = {n + 1, m + 1, z + 1};

        int type;
        while (q--) {
            scanf("%d", &type);
            if (type != 3) {
                int l, r;
                scanf("%d%d", &l, &r);
                trees[type].update(l , r , 1);
            } else {
                int x1, y1, z1, x2, y2, z2;
                scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);

                long long x = trees[0].query(x1 , x2);
                long long xx = x2 - x1 + 1 - x;
                long long y = trees[1].query(y1 , y2);
                long long yy = y2 - y1 + 1 - y;
                long long z = trees[2].query(z1 , z2);
                long long zz = z2 - z1 + 1 - z;
                long long ans = x * y * z + x * yy * zz + xx * y * zz + xx * yy * z;

                printf("%lld\n" , ans);
            }
        }
    }
}