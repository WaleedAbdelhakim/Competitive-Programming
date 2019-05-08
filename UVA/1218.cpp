#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;
int n;
vector<int> adj[N];
int memo[N][3];

int solve (int node , int state , int par) {
    int &ret = memo[node][state];
    if (~ret)
        return ret;

    int b = 1 , w = 0 , mn = N;
    for (int child : adj[node]) {
        if (child == par) continue;
        b += solve(child , 0 , node);
        w += solve(child , 1 , node);
        mn = min(mn , solve(child , 2 , node) - solve(child , 1 , node));
    }

    if (state == 0)
        ret = min(b , w + (node == 1 ? mn : 0));
    else if (state == 1)
        ret = w + mn;
    else
        ret = b;

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    while (scanf("%d" , &n) == 1) {
        int u , v;
        fill(adj + 1 , adj + n + 1 , vector<int>());
        for (int i = 0 ;i < n - 1 ;i++) {
            scanf("%d%d" , &u , &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        memset(memo , -1 , sizeof memo);
        printf("%d\n" , solve(1 , 0 , 1));

        scanf("%d" , &u);
        if (!~u)
            break;
    }
}