#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template<typename T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 1e4 + 5, M = 1e4 + 5;
int n, q;
int a[N], st[M], en[M], ind[M];
long long mean[M] ;
int median[M] , mode[M];

map<int , int> f;
set<pair<int , int> > fs;
Tree<pair<int , int> > os;
long long sum;

void add(int i) {
    fs.erase({f[a[i]] , a[i]});
    f[a[i]]++;
    fs.insert({f[a[i]] , a[i]});
    os.insert({a[i] , i});
    sum += a[i];
}

void remove(int i) {
    fs.erase({f[a[i]] , a[i]});
    f[a[i]]--;
    fs.insert({f[a[i]] , a[i]});
    os.erase({a[i] , i});
    sum -= a[i];
}

void mo() {
    int bsz = sqrt(n);
    sort(ind, ind + q, [bsz](int i, int j) {
        int ibid = st[i] / bsz, jbid = st[j] / bsz;
        return tie(ibid, en[i]) < tie(jbid, en[j]);
    });

    int s = 0, e = -1;
    for (int j = 0; j < q; j++) {
        int i = ind[j];
        while (e < en[i])
            add(++e);
        while (e > en[i])
            remove(e--);
        while (s < st[i])
            remove(s++);
        while (s > st[i])
            add(--s);

        mean[i] = sum / (en[i] - st[i] + 1);
        int len = en[i] - st[i] + 1;
        if ((en[i] - st[i])&1) {
            median[i] = (os.find_by_order(len / 2 - 1)->first + os.find_by_order(len / 2)->first) / 2;
        } else {
            median[i] = os.find_by_order(len / 2)->first;
        }
        mode[i] = fs.rbegin()->second;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d%d", st + i, en + i);
        ind[i] = i;
    }

    mo();

    for (int i = 0; i < q; i++)
        printf("%lld %d %d\n", mean[i] , median[i] , mode[i]);
}