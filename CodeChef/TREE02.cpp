#include <bits/stdc++.h>

using namespace std;

const int N = 2e4 + 5;
int n , k , w[N];
vector<int> adj[N];
vector<long long> temp;
long long val[N];

int dfs(int node , int par , long long mx) {
    int ret = 0;
    for (int child : adj[node])
        if (child != par)
            ret += dfs(child, node, mx);

    temp.clear();
    for (int child : adj[node])
        if (child != par)
            temp.push_back(val[child]);

    sort(temp.begin() , temp.end());

    val[node] = w[node];
    for (auto x : temp)
        if (val[node] + x <= mx)
            val[node] += x , ret++;

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    scanf("%d%d" , &n , &k);

    long long l = 0 , r = 0 , theOne = -1;
    for (int i = 1 ;i <= n ;i++) {
        scanf("%d" , w + i);
        l = max(l , 1ll * w[i]);
        r += w[i];
    }

    int u , v;
    for (int i = 0 ;i < n - 1 ;i++) {
        scanf("%d%d" , &u , &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    while (l <= r) {
        long long mid = (l + r) / 2;
        if (n - dfs(1 , 1 , mid) <= k) {
            theOne = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    printf("%lld\n" , theOne);
}
