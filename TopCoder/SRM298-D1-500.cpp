#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
vector<int> adj[N];
int in[N] , out[N];

bool vis[N];
int reach(int node) {
    vis[node] = 1;
    int cnt = 1;
    for (int child : adj[node])
        if (!vis[child])
            cnt += reach(child);
    return cnt;
}

class OrderDoesMatter {
public:
    int getOrder(vector <int> a, vector <int> b) {
        set<int> uni;
        for (int i = 0 ;i < a.size() ;i++) {
            uni.insert(b[i]);
            uni.insert(a[i]);
        }

        for (int i = 0 ;i < a.size() ;i++) {
            adj[a[i]].push_back(b[i]);
            in[b[i]]++;
            out[a[i]]++;
        }

        vector<int> starts , ends;
        for (int x : uni) {
            if (abs(in[x] - out[x]) > 1) return -1;
            if (in[x] == out[x] + 1) ends.push_back(x);
            if (in[x] == out[x] - 1) starts.push_back(x);
        }

        if (!starts.size() && !ends.size() && reach(a[0]) == uni.size())
            return *uni.rbegin() * *uni.rbegin();

        if (starts.size() == 1 && ends.size() == 1 && reach(starts[0]) == uni.size())
            return starts[0] * ends[0];

        return -1;
    }
};
