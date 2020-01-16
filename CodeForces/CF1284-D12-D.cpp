#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int a[N] , b[N] , c[N] , d[N] , ind[N] , n;

class segtree {
    struct node {
        int mn_end = 1e9 , mx_start = -1;
        inline node operator +(const node &other) const {
            node ret = *this;
            ret.mn_end = min(ret.mn_end , other.mn_end);
            ret.mx_start = max(ret.mx_start , other.mx_start);
            return ret;
        }
    };

    inline int left(int p) { return p << 1; }
    inline int right(int p) { return (p << 1) + 1; }

    int n;
    vector<node> tree;

    void update (int i , pair<int , int> v , int l, int r, int p) {
        if (i > r || i < l)
            return;

        tree[p].mn_end = min(tree[p].mn_end , v.second);
        tree[p].mx_start = max(tree[p].mx_start , v.first);

        if (l == r)
            return;

        int mid = (l + r) >> 1;
        update(i , v , l, mid, left(p));
        update(i , v ,  mid + 1, r, right(p));
    }

    node query(int s , int e , int l , int r , int p) {
        if (l >= s && r <= e) return tree[p];
        int mid = (l + r) >> 1;
        if (e <= mid)
            return query(s , e , l , mid , left(p));
        else if (s > mid)
            return query(s , e , mid + 1 , r , right(p));
        return query(s , e , l , mid , left(p)) + query(s , e , mid + 1 , r , right(p));
    }

public:
    segtree(int _n) : n(_n + 1) {tree.resize(4 * n);} // will need to build if every leaf has it's own initalization

    void update(int p, pair<int ,int> v) {
        update(p , v, 0, n - 1, 1);
    }

    bool query(int s, int e , int c , int d) {
        node r = query(s, e, 0, n - 1, 1);
        return r.mn_end < c || r.mx_start > d;
    }
};

bool go() {
    sort(ind , ind + n , [&](int i , int j) {
        return a[i] < a[j];
    });

    segtree st(4 * N);
    for (int j = 0 ;j < n ;j++) {
        int i = ind[j];
        if (st.query(a[i] , 4 * N, c[i] , d[i]))
            return 0;
        st.update(b[i] , {c[i] , d[i]});
    }

    return 1;
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    cin >> n;

    map<int , int> New;
    for (int i = 0 ;i < n ;i++) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
        ind[i] = i;
        New[a[i]];
        New[b[i]];
        New[c[i]];
        New[d[i]];
    }

    int nxt = 1;
    for (auto &p : New)
        p.second = nxt++;

    for (int i = 0 ;i < n ;i++) {
        a[i] = New[a[i]];
        b[i] = New[b[i]];
        c[i] = New[c[i]];
        d[i] = New[d[i]];
    }


    bool ok = go();
    for (int i = 0 ;i < n ;i++) {
        swap(a[i] , c[i]);
        swap(b[i] , d[i]);
    }

    if (ok && go())
        cout << "YES";
    else
        cout << "NO";
}