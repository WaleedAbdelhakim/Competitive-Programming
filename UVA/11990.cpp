#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct BIT {
    vector<o_set<int> > tree;
    BIT(int n) : tree(n + 2){}

    void in(int p , int v) {
        for (int i = ++p ;i < tree.size() ; i += i & -i)
            tree[i].insert(v);
    }

    void del(int p , int v) {
        for (int i = ++p ;i < tree.size() ; i += i & -i)
            tree[i].erase(v);
    }

    int get(int p , int v , bool smaller) {
        int sum = 0;
        for (int i = ++p; i ; i -= i & -i) {
            if (smaller)
                sum += tree[i].order_of_key(v);
            else
                sum += tree[i].size() - tree[i].order_of_key(v + 1);
        }
        return sum;
    }

    int query(int l , int r , int v , bool b) {
        return get(r , v , b) - get(l - 1 , v , b);
    }
};

const int N = 2e5 + 5;
int pos[N];

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int n , m;
    while (scanf("%d%d" , &n , &m) == 2) {
        int x;
        long long inv = 0;
        BIT bit(n);
        for (int i = 0 ;i < n ;i++) {
            scanf("%d" , &x);
            pos[x] = i;
            inv += bit.get(i , x , 0);
            bit.in(i , x);
        }

        int e;
        while (m--) {
            scanf("%d" , &e);
            printf("%lld\n" , inv);
            inv -= bit.get(pos[e], e , 0) + bit.query(pos[e] , n - 1 , e , 1);
            bit.del(pos[e] , e);
        }
    }
}