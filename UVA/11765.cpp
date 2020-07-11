#include <bits/stdc++.h>

using namespace std;

//  (EV * min(flow , V))
// (EsqrtV) on bibrtite graphs

struct edge {
    int to;
    long long cap;
};

const int N = 205; // make sure is greater than max_node will ever be
int dist[N] , p[N] , src , max_node , snk; // don't forget to set src and snk
vector<edge> edges;
vector<int> network[N]; // adjacency list for maxflow

void addAugEdge(int u , int v , long long c) {
    max_node = max(max_node , max(u , v));
    network[u].push_back(edges.size());
    edges.push_back({v , c});
    network[v].push_back(edges.size());
    edges.push_back({u , c}); // c if undirected 0 if directed
}

bool BFS() {
    memset(dist , -1 , (max_node + 1) * sizeof dist[0]);
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    while (q.size()) {
        int cur = q.front();
        q.pop();
        for (int ci : network[cur]) {
            auto &e = edges[ci];
            if (dist[e.to] == -1 && e.cap) {
                q.push(e.to);
                dist[e.to] = dist[cur] + 1;
            }
        }
    }

    return max_node >= snk && dist[snk] != -1;
}

long long DFS(int node , long long flow) {
    if (node == snk || !flow)
        return flow;

    for (; p[node] < network[node].size() ; p[node]++) {
        auto &e= edges[network[node][p[node]]];
        auto &re = edges[network[node][p[node]]^1];

        if (dist[node] + 1  != dist[e.to]) continue;

        long long push = DFS(e.to , min(flow , e.cap));
        if (push) {
            e.cap -= push;
            re.cap += push;
            return push;
        }
    }

    return 0;
}

long long dinic() {
    long long flow = 0;
    while (BFS()) {
        memset(p , 0 , sizeof p);
        while (long long f = DFS(src , 1e17)) // make sure that no edge has cap greater than 1e9
            flow += f;
    }
    return flow;
}

void init() { // every test case
    edges.clear();
    for (int i = 0 ;i <= max_node;i++)
        network[i].clear();
    max_node = 0;
}

int top[N] , bott[N];

void run() {
    init();

    int n , m;
    cin >> n >> m;

    for (int i = 0 ;i < n ; i++)
        cin >> top[i];

    for (int i = 0 ;i < n ;i++)
        cin >> bott[i];

    src = n;
    snk = n + 1;

    for (int i = 0 ;i < n ;i++) {
        int t;
        cin >> t;

        if (t == 1) {
            addAugEdge(src , i , 1e16);
            addAugEdge(i , snk , top[i]);
        } else if (t == -1) {
            addAugEdge(src , i , bott[i]);
            addAugEdge(i , snk , 1e16);
        } else {
            addAugEdge(src , i , bott[i]);
            addAugEdge(i , snk , top[i]);
        }
    }

    while (m--) {
        int u , v , c;
        cin >> u >> v >> c;
        addAugEdge(u - 1 , v - 1, c);
    }

    cout << dinic() << '\n';
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in", "r" , stdin);
#endif
    int t;
    cin >> t;
    while (t--)
        run();
}
