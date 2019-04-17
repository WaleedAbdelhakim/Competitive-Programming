#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int n , m , d;
bool eff[N];

vector<int> adj[N] , s[N];
multiset<int> info[N];

int mx(int node , int par) {
    info[node].insert(eff[node] ? 0 : -1e9);
    for (int child : adj[node]) {
        if (child != par) {
            int c = mx(child , node) + 1;
            info[node].insert(c);
            s[node].push_back(c);
        } else {
            s[node].push_back(-1e9);
        }
    }
    return *info[node].rbegin();
}

int count(int node , int par , int mxup) {
    int ret = max(mxup , *info[node].rbegin()) <= d;
    for (int i = 0 ;i < adj[node].size() ;i++) {
        int child = adj[node][i];
        if (child != par) {
            info[node].erase(info[node].find(s[node][i]));
            ret += count(child , node , max(*info[node].rbegin() , mxup) + 1);
            info[node].insert(s[node][i]);
        }
    }
    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    scanf("%d%d%d" , &n , &m , &d);

    int u , v;
    while (m--) {
        scanf("%d" , &u);
        eff[u] = 1;
    }

    for (int i = 0 ;i < n - 1 ;i++) {
        scanf("%d%d" , &u , &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    mx(1 , 1);
    printf("%d" , count(1 , 1 , -1e9));
}