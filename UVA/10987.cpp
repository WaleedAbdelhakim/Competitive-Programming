#include <bits/stdc++.h>

using namespace std;

const int N = 105;

struct edge {
    int to;
    long long  cost;
};

struct path {
    int node;
    long long  cost;
    bool operator < (const path &other) const {
        return cost > other.cost;
    }
};

bool known[N];
long long  org[N][N] , dist[N][N];
vector<edge> adj[N];

void Dijkstra(int s , int d , bool skip) {
    priority_queue<path> pq;
    memset(known , 0 , sizeof known);
    memset(dist[s] , 63 , sizeof dist[s]);

    pq.push({s , 0});
    dist[s][s] = 0;

    while (pq.size()) {
        int node = pq.top().node;
        long long  cost = pq.top().cost;
        pq.pop();

        if (known[node]) continue;
        known[node] = 1;

        for (auto &c : adj[node]) {
            if (skip && node == s && c.to == d) continue;
            if (dist[s][c.to] > dist[s][node] + c.cost) {
                dist[s][c.to] = dist[s][node] + c.cost;
                pq.push({c.to , dist[s][c.to]});
            }
        }
    }

}

bool valid(int n) {
    for (int i = 1 ;i <= n ;i++)
        Dijkstra(i , -1 , 0);

    for (int i = 1 ;i <= n ;i++)
        for (int j = 1 ;j <= n ;j++)
            if (org[i][j] != dist[i][j])
                return 0;
    return 1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T , n;
    scanf("%d" , &T);
    for (int t = 1 ; t <= T ; t++) {
        scanf("%d" , &n);

        fill(adj , adj + N , vector<edge>());

        for (int i = 2 ;i <= n ;i++) {
            int c;
            for (int j = 1 ;j < i ;j++) {
                scanf("%d" , &c);
                org[i][j] = org[j][i] = c;
                adj[i].push_back({j , c});
                adj[j].push_back({i , c});
            }
        }

        printf("Case #%d:\n" , t);
        if (!valid(n)) {
            puts("Need better measurements.\n");
            continue;
        }

        vector<pair<int , int> > ans;
        for (int i = 1 ;i <= n ;i++) {
            for (int j = i + 1 ;j <= n ;j++) {
                Dijkstra(i , j , 1);
                if (dist[i][j] != org[i][j])
                    ans.push_back({i , j});
            }
        }

        printf("%d\n" , ans.size());
        for (auto c : ans)
            printf("%d %d %d\n" , c.first , c.second , org[c.first][c.second]);
        puts("");
    }
}