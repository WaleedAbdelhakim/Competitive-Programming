#include <bits/stdc++.h>

using namespace std;

const int N = 55;
vector<int> adj[N];
bool vis[N];
int dfs(int u) {
    vis[u] = 1;
    for (int v : adj[u])
        if (!vis[v])
            dfs(v);
}

class PerfectPermutation {
public:
    int reorder(vector <int> v) {
        for (int i = 0 ;i < v.size() ;i++)
            adj[i].push_back(v[i]);

        int cnt = 0;
        for (int i = 0 ;i < v.size() ;i++)
            if (!vis[i])
                dfs(i) , cnt++;

        return cnt == 1 ? 0 : cnt;
    }
};
