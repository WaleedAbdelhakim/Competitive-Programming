#pragma GCC optimize ("O3")

#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

//typedef tree<pair<int , int> , null_type, less<pair<int , int> >, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef vector<int> vi;
typedef long long ll;

#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
#define watch(x) cout << (#x) << " is " << (x) << endl

int di[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dj[] = {1, -1, 0, 0, -1, 1, 1, -1};

const int N = 3e5 + 5 , M = sqrt(N) + 5;
int n, m, u , bsz;
ll arr[N];
vector<ll>  block[M];

void build() {
    bsz = sqrt(n);
    for (int i = 0 ;i < n ;i++)
        block[i / bsz].pb(arr[i]);

    for (int i = 0 ;block[i].size();i++)
        sort(all(block[i]));
}

int query(int l , int r , int k) {
    int cnt = 0;
    if(l / bsz == r / bsz) {
        while(l <= r)
            cnt += arr[l++] < k;
    } else {
        while(l % bsz != 0)
            cnt += arr[l++] < k;
        while((r + 1) % bsz != 0)
            cnt += arr[r--] < k;

        int a = l / bsz , b = r / bsz;
        for (int i = a ;i <= b ;i++)
            cnt += lower_bound(all(block[i]) , k) - block[i].begin();
    }

    return cnt;
}

void update(int ind , ll val) {
    int bid = ind / bsz;
    int pos = lower_bound(all(block[bid]) , arr[ind]) - block[bid].begin();
    arr[ind] = block[bid][pos] = val;
    while(pos  + 1 < block[bid].size() && block[bid][pos] > block[bid][pos + 1]) {
        swap(block[bid][pos] , block[bid][pos + 1]);
        pos++;
    }

    while(pos > 0 && block[bid][pos] < block[bid][pos - 1]) {
        swap(block[bid][pos] , block[bid][pos - 1]);
        pos--;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    scanf("%d %d %d", &n, &m, &u);
    for (int i = 0 ;i < n ;i++)
        scanf("%d" , arr + i);

    build();

    int l , r , v , p;
    while(m--) {
        scanf("%d%d%d%d",&l,&r,&v,&p);
        l-- , r-- , p--;
        int k = query(l , r , v);
        update(p , (u * 1ll * k) / (r - l + 1));
    }

    for (int i = 0 ;i < n ;i++)
        printf("%lld\n" , arr[i]);
}