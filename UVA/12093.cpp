#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;
vector<int> temp[N] , adj[N];
int dp[N][4] , n , nc , sc;

void dfs (int node) {
    for (int c : adj[node])
        dfs(c);

    if (adj[node].empty()) {
        dp[node][0] = sc;
        dp[node][1] = nc;
        dp[node][2] = 0;
        dp[node][3] = 0;
        return;
    }

    int sum0 = 0 , sum1  = 0 , sum2 = 0 , sum3 = 0;
    for (int c : adj[node]) {
        sum0 += dp[c][0];
        sum1 += dp[c][1];
        sum2 += dp[c][2];
        sum3 += dp[c][3];
    }

    dp[node][0] = sum3 + sc;
    dp[node][1] = min(sum2 + nc , sum0);
    dp[node][2] = min(sum2 + nc , min(sum1 , sum3 + sc));
    dp[node][3] = min(sum3 + sc , sum2);

    for (int c: adj[node]) {
        int cur = sc + sum2 - dp[c][2];
        for (int c2 : adj[c])
            cur += dp[c2][3];
        dp[node][1] = min(dp[node][1] , cur);
        dp[node][2] = min(dp[node][2] , cur);
    }
}

void dfs(int node , int par) {
    for (int child : temp[node]) {
        if (child != par) {
            adj[node].push_back(child);
            dfs(child , node);
        }
    }
}

void solve () {
    fill(adj , adj + (n + 1) , vector<int>());
    fill(temp , temp + (n + 1) , vector<int>());

    int u , v;
    for (int i = 0 ;i < n - 1 ;i++) {
        cin >> u >> v;
        temp[v].push_back(u);
        temp[u].push_back(v);
    }

    dfs(1 , 1);
    dfs(1);

    cout << dp[1][2] << '\n';
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
    while (cin >> n >> nc >> sc , n)
        solve();
}
