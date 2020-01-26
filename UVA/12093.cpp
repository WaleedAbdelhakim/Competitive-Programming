/*
    explanation : 

    let p[u] be the parent of node u
    let e(u, v) be the edge connecting node u and v
    
    dp[u][0] = min cost to protect subtree(u) knowing that e(u , p[u]) is not protected
    dp[u][1] = min cost to protect subtree(u) 
    dp[u][2] = min cost to protect subtree(u) knowing that all the edges directly connected to node u are protected
   
    options for each state
    
    state(0): 1. we can put a normal soldier and every child will have a state 1
              2. to leave the current node empty and choose one of the children to be super and the rest of them will have state 1
    state(1): 1. to leave the current node empty and every child will have a state 0
              2. to put a normal soldier and every child will have a state 1
              3. to put a super soldier and every child will have a state 2
              4. to leave the current node empty and choose one child to be super and the rest will have state 1
    state(2): 1. to put a super soldier and every child will have a state 2
              2. to leave it empty and every child will have a state 1
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;
vector<int> temp[N] , adj[N];
int dp[N][3] , n , nc , sc;

void dfs (int node) {
    for (int c : adj[node])
        dfs(c);

    int sum0  = 0 , sum1 = 0 , sum2 = 0;
    for (int c : adj[node]) {
        sum0 += dp[c][0];
        sum1 += dp[c][1];
        sum2 += dp[c][2];
    }

    dp[node][0] = sum1 + nc;
    dp[node][1] = min(sum1 + nc , min(sum0 , sum2 + sc));
    dp[node][2] = min(sum2 + sc , sum1);

    for (int c: adj[node]) {
        int cur = sc + sum1 - dp[c][1];
        for (int c2 : adj[c])
            cur += dp[c2][2];
        dp[node][0] = min(dp[node][0] , cur);
        dp[node][1] = min(dp[node][1] , cur);
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

    cout << dp[1][1] << '\n';
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
    while (cin >> n >> nc >> sc , n)
        solve();
}
