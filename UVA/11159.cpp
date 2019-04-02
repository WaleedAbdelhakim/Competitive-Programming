#include <bits/stdc++.h>

using namespace std;

struct edge {
    int to , cap;
};

const int N = 300; // make sure is greater than max_node will ever be
int dist[N] , p[N] , src , max_node , snk; // don't forget to set src and snk
vector<edge> edges;
vector<int> adj[N];

void addAugEdge(int u , int v , int c) {
    max_node = max(max_node , max(u , v));
    adj[u].push_back(edges.size());
    edges.push_back({v , c});
    adj[v].push_back(edges.size());
    edges.push_back({u , 0}); // c if undirected 0 if directed
}

bool bfs() {
    memset(dist , -1 , (max_node + 1) * sizeof dist[0]);
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    while (q.size()) {
        int cur = q.front();
        q.pop();
        for (int ci : adj[cur]) {
            auto &e = edges[ci];
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
        auto &e= edges[adj[node][p[node]]];
        auto &re = edges[adj[node][p[node]]^1];

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

void init() { // every test case
    edges.clear();
    for (int i = 0 ;i <= max_node;i++)
        adj[i].clear();
    max_node = 0;
}


int a[N];
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int T , n , m , x;
    scanf("%d" , &T);
    for (int test = 1 ; test <= T ; test++) {
        init();
        scanf("%d" , &n);

        src = N - 1 , snk = N - 2;
        for (int i = 0 ;i < n ;i++) {
            scanf("%d" , a + i);
            addAugEdge(src , i , 1);
        }

        scanf("%d" , &m);
        for (int i = 0 ;i < m ;i++) {
            scanf("%d" , &x);
            for (int j = 0 ;j < n ;j++)
                if ((!x && !a[j]) || (a[j] && x % a[j] == 0))
                    addAugEdge(j , i + n , 1);

            addAugEdge(i + n , snk , 1);
        }

        printf("Case %d: %d\n" , test , dinic());
    }
}



