#include <bits/stdc++.h>

using namespace std;

// O(EV^2)
struct edge {
    int to , cap;
};

const int N = 1e3 + 10; // make sure is greater than max_node will ever be
int dist[N] , p[N] , src , max_node , snk; // don't forget to set src and snk
vector<edge> edges;
vector<int> network[N]; // adjacency list for maxflow

void addAugEdge(int u , int v , int c) {
    max_node = max(max_node , max(u , v));
    network[u].push_back(edges.size());
    edges.push_back({v , c});
    network[v].push_back(edges.size());
    edges.push_back({u , 0}); // c if undirected 0 if directed
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

int DFS(int node , int flow) {
    if (node == snk || !flow)
        return flow;

    for (; p[node] < network[node].size() ; p[node]++) {
        auto &e= edges[network[node][p[node]]];
        auto &re = edges[network[node][p[node]]^1];

        if (dist[node] + 1  != dist[e.to]) continue;

        int push = DFS(e.to , min(flow , e.cap));
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
        while (int f = DFS(src , 1e9)) // make sure that no edge has cap greater than 1e9
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

#define from first
#define to second.first
#define cost second.second

int d[N];
void run_case() {
    init();
    int t , n , m;
    cin >> t >> n >> m >> src >> snk;

    vector<pair<int , pair<int , int> > > edges (m);

    for (int i = 0 ;i < m ;i++) {
        cin >> edges[i].from >> edges[i].to >> edges[i].cost;
        addAugEdge(edges[i].from  , edges[i].to , edges[i].cost);
    }

    for (int i = 0 ;i < n ;i++)
        d[i] = -1e9;

    d[src] = 1e9;
    for (int i = 0 ;i < n ;i++)
        for (auto &e : edges)
            if (d[e.to] < min(d[e.from] , e.cost))
                d[e.to] = min(d[e.from] , e.cost);

    cout << fixed << setprecision(3) << t << ' ' << (dinic() + 0.0) / d[snk] << '\n';
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int t;
    cin >> t;
    while (t--)
        run_case();
}