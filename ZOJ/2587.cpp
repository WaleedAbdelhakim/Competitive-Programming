// let A and B be the supercomputers we want to disconnect 
// run maxflow with source = A and sink = B
// and get the set of edges that represent the cut 
// then recalculate the cut with source = B and sink = A
// if there are multiple solutions the two cuts will never be the same 

#include <bits/stdc++.h>
using namespace std;

struct edge {
    int to , cap;
};

const int N = 805; // make sure is greater than max_node will ever be
int dist[N] , p[N] , src , max_node , snk; // don't forget to set src and snk
vector<edge> edges;
vector<int> adj[N];

void addAugEdge(int u , int v , int c) {
    max_node = max(max_node , max(u , v));
    adj[u].push_back(edges.size());
    edges.push_back(edge{v , c});
    adj[v].push_back(edges.size());
    edges.push_back(edge{u , c}); // c if undirected 0 if directed
}

bool bfs() {
    memset(dist , -1 , (max_node + 1) * sizeof dist[0]);
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    while (q.size()) {
        int cur = q.front();
        q.pop();

        for (int j = 0 ;j < adj[cur].size() ;j++) {
            int ci = adj[cur][j];
            edge &e = edges[ci];
            if (dist[e.to] == -1 && e.cap) {
                q.push(e.to);
                dist[e.to] = dist[cur] + 1;
            }
        }
    }

    return max_node >= snk && dist[snk] != -1;
}

int dfs (int node , int flow) {
    if (node == snk || !flow)
        return flow;

    for (; p[node] < adj[node].size() ; p[node]++) {
        edge &e= edges[adj[node][p[node]]];
        edge &re = edges[adj[node][p[node]]^1];

        if (dist[node] + 1  != dist[e.to]) continue;

        int push = dfs(e.to , min(flow , e.cap));
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
    while (bfs()) {
        memset(p , 0 , sizeof p);
        while (int f = dfs(src , 1e9)) // make sure that no edge has cap greater than 1e9
            flow += f;
    }
    return flow;
}

int vis[N] , vid;
void go (int node) {
    vis[node] = vid;
    for (int j = 0 ;j < adj[node].size() ;j++) {
        int ei = adj[node][j];
        edge &e = edges[ei];
        if (e.cap && vis[e.to] != vid)
            go(e.to);
    }
}

void init() { // every test case
    edges.clear();
    for (int i = 0 ;i <= max_node;i++)
        adj[i].clear();
    max_node = 0;
}

vector<pair<pair<int , int>  , int> > info;
set<pair<int , int> > get(int s , int t ,int n) {
    init();
    for (int i = 0 ;i < info.size() ;i++)
        addAugEdge(info[i].first.first , info[i].first.second , info[i].second);
    src = s , snk = t;
    dinic();
    ++vid;
    go(s);
    set<pair<int , int> > f;
    for (int i = 1 ;i <= n ;i++) {
        if (vis[i] == vid) {
            for (int j = 0 ;j < adj[i].size() ;j++) {
                int ei = adj[i][j];
                edge &e = edges[ei];
                if (vis[e.to] != vid)
                    f.insert({min(i , e.to) , max(i , e.to)});
            }
        }
    }
    return f;
}
int main() {
    int n , m , x , y;
    while (scanf("%d%d%d%d" , &n , &m , &x , &y) , n + m + x + y) {
        info.clear();
        int u , v , c;
        while (m--) {
            scanf("%d%d%d" , &u , &v , &c);
            info.push_back(make_pair(make_pair(u , v) , c));
        }
        puts(get(x , y , n) == get(y , x , n) ? "UNIQUE" : "AMBIGUOUS");
    }
}