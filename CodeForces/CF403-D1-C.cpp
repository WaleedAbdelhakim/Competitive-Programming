#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 5;
int vis[N] , m[N][N] , vid = 1, n;
int dfs(int node) {
    int ret = 1;
    vis[node] = vid;
    for (int child = 0 ; child < n ; child++)
        if (m[node][child] && vis[child] != vid)
            ret += dfs(child);
    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    scanf("%d" , &n);
    for (int i = 0 ;i < n ;i++) {
        for (int j = 0 ;j < n ;j++) {
            int x;
            scanf("%d" , &x);
            if (i != j) m[i][j] = x;
        }
    }

    bool yes = dfs(0) == n;
    for (int i = 0 ;i < n ;i++)
        for (int j = i + 1 ;j < n ;j++)
            swap(m[i][j] , m[j][i]);

    ++vid;
    yes &= dfs(0) == n;
    puts(yes ? "YES" : "NO");
}
