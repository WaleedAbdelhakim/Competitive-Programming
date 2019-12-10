#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <math.h>
#include <iomanip>

using namespace std;

struct edge {
    int to ;
    double cap;
    edge(int _to , double _cap) : to(_to) , cap(_cap) {}
};

const int N = 105; // make sure is greater than max_node will ever be
int dist[N] , p[N] , src , max_node , snk; // don't forget to set src and snk
vector<edge> edges;
vector<int> network[N]; // adjacency list for maxflow

void addAugEdge(int u , int v , double c) {
    max_node = max(max_node , max(u , v));
    network[u].push_back(edges.size());
    edges.push_back(edge(v , c));
    network[v].push_back(edges.size());
    edges.push_back(edge(u , 0)); // c if undirected 0 if directed
}

bool BFS() {
    memset(dist , -1 , (max_node + 1) * sizeof dist[0]);
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    while (q.size()) {
        int cur = q.front();
        q.pop();
        for (int i = 0 ;i < network[cur].size() ;i++) {
            int ci = network[cur][i];
            edge &e = edges[ci];
            if (dist[e.to] == -1 && e.cap) {
                q.push(e.to);
                dist[e.to] = dist[cur] + 1;
            }
        }
    }

    return max_node >= snk && dist[snk] != -1;
}

double DFS(int node , double flow) {
    if (node == snk || !flow)
        return flow;

    for (; p[node] < network[node].size() ; p[node]++) {
        edge &e= edges[network[node][p[node]]];
        edge &re = edges[network[node][p[node]]^1];

        if (dist[node] + 1  != dist[e.to]) continue;

        double push = DFS(e.to , min(flow , e.cap));
        if (push) {
            e.cap -= push;
            re.cap += push;
            return push;
        }
    }

    return 0;
}

double dinic() {
    double flow = 0;
    while (BFS()) {
        memset(p , 0 , sizeof p);
        while (double f = DFS(src , 1e9)) // make sure that no edge has cap greater than 1e9
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

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n , m , q;
        cin >> n >> m >> q;

        init();

        src = N - 1;
        snk = N - 2;

        double x;
        for (int i = 0 ;i < n ;i++) {
            cin >> x;
            addAugEdge(src , i , log(x));
        }

        for (int i = 0 ;i < m ;i++) {
            cin >> x;
            addAugEdge(i + n, snk , log(x));
        }

        int r , c;
        while (q--) {
            cin >> r >> c;
            addAugEdge(r - 1 , c - 1 + n , 1e9);
        }

        cout << fixed << setprecision(4) << exp(dinic()) << '\n';
    }
}