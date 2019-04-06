#include <bits/stdc++.h>

using namespace std;

#define inf 0x3f3f3f3f3f3f3f3f // change if dist is int array

struct edge {
    int from, to, cap, unit_cost;
};

const int N = 110; // make sure is greater than max_node will ever be
long long dist[N];
int par[N] , max_node , src, snk; // don't forget to set src and snk
bool inq[N];

vector<edge> edges;
vector<int> adj[N];

bool spfa() {
    memset(dist, '?' , (max_node + 1) * sizeof dist[0]);
    memset(inq, 0, (max_node + 1) * sizeof inq[0]);
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

    return max_node >= snk && dist[snk] != inf;
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

void addAugEdge(int u, int v, int cap, int cost) {
    max_node = max(max_node , max(u , v));
    adj[u].push_back(edges.size());
    edges.push_back({u, v, cap, -cost});
    adj[v].push_back(edges.size());
    edges.push_back({v, u, 0, cost}); // c if undirected 0 if directed
}

pair<long long , long long> mcmf() {
    long long flow = 0, cost = 0;
    while (spfa()) {
        int f = augment(par[snk], 1e9); // make sure 1e9 is greater than max cap
        flow += f;
        cost += f * 1ll * -dist[snk];
    }
    return {flow, cost};
}

void init() {
    edges.clear();
    for (int i = 0; i <= max_node ; i++)
        adj[i].clear();
    max_node = 0;
}

const double EPS = 1e-5;
int a[N] , aa[N];
double mat[N][N];

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int n , m , test = 1;
    while (cin >> n >> m , n + m) {
        init();
        src = N - 1 , snk = N - 2;
        for (int i = 0 ;i < n ;i++) {
            cin >> a[i];
            addAugEdge(src , i , a[i] , 0);
        }

        for (int i = 0 ;i < m ;i++) {
            cin >> aa[i];
            addAugEdge(i + n , snk , aa[i] , 0);
        }

        for (int i = 0 ;i < n ;i++) {
            for (int j = 0 ;j < m ;j++) {
                cin >> mat[i][j];
                int c = (mat[i][j] + EPS) * 100;
                if (mat[i][j] != -1)
                    addAugEdge(i , j + n , 1e9 , c);
            }
        }

        double b = mcmf().second / 100.0;
        init();
        for (int i = 0 ;i < n ;i++)
            addAugEdge(src , i , a[i] , 0);
        for (int i = 0 ;i < m ;i++)
            addAugEdge(i + n , snk , aa[i] , 0);
        for (int i = 0 ;i < n ;i++)
            for (int j = 0 ;j < m ;j++)
                if (mat[i][j] != -1) {
                    int c = (mat[i][j] + EPS) * -100;
                    addAugEdge(i , j + n , 1e9 , c);
                }

        double a = mcmf().second / -100.0;
        cout << fixed << setprecision(2) << "Problem " << test++ << ": " << a << " to " << b << "\n";
    }
}
