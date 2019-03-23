#pragma GCC optimize ("O3")

#include <bits/stdc++.h>

using namespace std;

#define inf 0x3f3f3f3f

const int N = 210;
int n;

struct edge {
    int from, to, cap, unit_cost;
};

vector<edge> edges;
vector<int> adj[N];

int dist[N], par[N], cost[26][26], src, snk;
bool inq[N];
char a[1005], b[105];

void addAugEdge(int u, int v, int cap, int cost) {
    adj[u].push_back(edges.size());
    edges.push_back({u, v, cap, cost});
    adj[v].push_back(edges.size());
    edges.push_back({v, u, 0, -cost}); // cap is 0 if undirected
}

bool spfa() {
    memset(dist, '?', (n + 1) * sizeof dist[0]);
    memset(inq, 0, (n + 1) * sizeof inq[0]);
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    inq[src] = 1;
    par[src] = -1;
    while (q.size()) {
        int u = q.front();
        inq[u] = 0;
        q.pop();
        for (int c : adj[u]) {
            auto &e = edges[c];
            if (!e.cap) continue;
            if (dist[e.to] > dist[u] + e.unit_cost) {
                dist[e.to] = dist[u] + e.unit_cost;
                par[e.to] = c;
                if (!inq[e.to]) {
                    inq[e.to] = 1;
                    q.push(e.to);
                }
            }
        }
    }
    return dist[snk] != inf;
}

int augment(int eid, int mn) {
    if (eid == -1) return mn;
    auto &e = edges[eid];
    auto &re = edges[eid ^ 1];
    int flow = augment(par[e.from], min(mn, e.cap));
    e.cap -= flow;
    re.cap += flow;
    return flow;
}

pair<int, int> mcmf() {
    int flow = 0, cost = 0;
    while (spfa()) {
        int f = augment(par[snk], inf);
        flow += f;
        cost += f * dist[snk];
    }
    return {flow, cost};
}

void init() {
    memset(cost, -1, sizeof cost);
    edges.clear();
    for (int i = 0; i < N; i++)
        adj[i].clear();
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--) {
        init();
        scanf("%s%s", a, b);

        int len = strlen(a);
        for (int i = len - 1; i > 0; i--)
            cost[a[i - 1] - 'a'][a[i] - 'a'] = i * i;

        len = strlen(b);
        n = 2 * len + 2;
        src = 2 * len, snk = 2 * len + 1;
        for (int i = 0; i < len; i++) {
            addAugEdge(src, i, 1, 0);
            addAugEdge(i + len, snk, 1, 0);
            for (int j = i + 1; j < len; j++)
                if (~cost[b[i] - 'a'][b[j] - 'a'])
                    addAugEdge(i, len + j, 1, cost[b[i] - 'a'][b[j] - 'a']);
        }

        auto ans = mcmf();
        printf("%d %d\n", len - ans.first, ans.second);
    }

}