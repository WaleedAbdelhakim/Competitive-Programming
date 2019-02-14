// as every edge's cost can be represented as the following equation : x * t + y
// that means that every path which is a summation of some edges
// also can be represented as the same equation
// looking at the problem this way leads to a simpler problem :
// given  some equations of that form knowing their x and y find the t that maximizes the minimum
// now if an equation has negative x that means it decreases as we increase t and vice versa
// so if we have all the equations with the same sign of x
// if it is negative then answer is 0
// if it is positive then answer is 1440
// until now the function either decreasing or increasing
// now what if we have equations with different signs
// imagine them as towers and each one either decrease or increase
/*
 *           ___
 *          |   |                  ___
 *          |   |           ___   |   |
 *    ___   |   |          |   |  |   |
 *   |   |  |   |   -->    |   |  |   |
 *   |   |  |   |          |   |  |   |
 *   |   |  |   |          |   |  |   |
 *     +      -              +      -
 */

// so as we increase t , we will get a new maximum until they cross
// in that case the function is Unimodal as we need to run ternery search
// and about the equations with x equal 0 it will only lead to functions with equal values
// in the beginning or at the peak , which isn't a problem
// so because we can't process all the paths in graph to get the minimum
// we will run Dijkstra to get the min equation value for a given t

#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using ll = long long;

#define pb push_back

struct edge {
    int to , a , b;
};

struct path {
    int node;
    double cost;
    bool operator < (const path &other) const {
        return cost > other.cost;
    }
};

const int N = 1005;
vector<edge> adj[N];
int known[N] , vid;
double dist[N];
int n , m;

double Dijkstra(double t) {
    priority_queue<path> pq;
    ++vid;
    for (int i = 1 ;i <= n ;i++)
        dist[i] = 2e9;

    pq.push({1 , 0});
    dist[1] = 0;

    while (pq.size()) {
        int node = pq.top().node;
        double cost = pq.top().cost;
        pq.pop();
        if (node == n) return cost;
        if (known[node] == vid) continue;

        known[node] = vid;
        for (auto &c : adj[node]) {
            if (dist[c.to] > dist[node] + c.a * t + c.b) {
                dist[c.to] = dist[node] + c.a * t + c.b;
                pq.push({c.to , dist[c.to]});
            }
        }
    }
}

double solve () {
    double l = 0 , r = 1440 , mx = 0;
    for (int i = 0 ;i < 100 ;i++) {
        double md1 = l + (r - l) / 3;
        double md2 = r - (r - l) / 3;
        double a = Dijkstra(md1) , b = Dijkstra(md2);
        mx = max(mx , max(a , b));

        if (b > a)
            l = md1;
        else
            r = md2;
    }
    return mx;
}

int main() {
    while (scanf("%d%d" , &n , &m) == 2) {
        for (int i = 1 ;i <= n ;i++)
            adj[i].clear();

        int u , v , a , b;
        while(m--) {
            scanf("%d%d%d%d" ,&u , &v , &a , &b);
            adj[u].pb({v , a , b});
            adj[v].pb({u , a , b});
        }


        printf("%.5f\n" , solve());
    }
}