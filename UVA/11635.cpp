#include <bits/stdc++.h>

//#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

//template<typename T>
//using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef vector<int> vi;
typedef long long ll;

#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
#define watch(x) cout << (#x) << " is " << (x) << endl

int di[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dj[] = {1, -1, 0, 0, -1, 1, 1, -1};

#define to second
#define cost first

const int N = 1e4 + 5 , M = 105;
int n ;
vector<pair<int , int> > adj[N];
vi info;

int dist[N] , d[M][M];

void Dijkstra(int s) {
    priority_queue<pair<int , int>  , vector<pair<int , int> > , greater<pair<int , int>>> pq;
    memset(dist , 63 , sizeof dist);
    dist[info[s]] = 0;
    pq.push({0 , info[s]});

    while(pq.size()) {
        auto cur = pq.top();
        pq.pop();

        if(dist[cur.to] < cur.cost) continue;

        for (auto & child : adj[cur.to]) {
            if(dist[child.to] > dist[cur.to] + child.cost) {
                dist[child.to] = dist[cur.to] + child.cost;
                pq.push({dist[child.to] , child.to});
            }
        }
    }

    for (int i = 0 ;i < info.size() ;i++)
        d[s][i] = dist[info[i]];
}

int memo[M][M];
int solve(int i , int hotles) {
    if(d[i][1] <= 600)
        return hotles;

    if(hotles > 100)
        return inf;

    int &ret = memo[i][hotles];
    if(~ret)
        return ret;

    ret = inf;
    for (int j = 2 ;j < info.size() ;j++)
        if(d[i][j] <= 600)
            ret = min(ret , solve(j , hotles + 1));

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    while(scanf("%d" , &n) , n) {
        int cnt , x;
        scanf("%d",&cnt);
        info.clear() , info.pb(1) , info.pb(n);
        for (int i = 0 ;i < cnt ;i++) {
            scanf("%d",&x);
            info.pb(x);
        }

        for (int i = 1 ;i < N ;i++)
            adj[i].clear();

        int m , a , b , c;
        scanf("%d",&m);
        while(m--) {
            scanf("%d%d%d",&a,&b,&c);
            adj[a].pb({c , b});
            adj[b].pb({c , a});
        }

        for (int i = 0 ;i < info.size() ;i++)
            Dijkstra(i);


        memset(memo , -1 , sizeof memo);
        int ans = solve(0 , 0);
        if(ans == inf)
            puts("-1");
        else
            printf("%d\n" , ans);
    }
}