#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1e5 + 5;
int n , m;
int vis[N] , low[N] , dfsTime[N] , Time;
vector<pair<int , int> > adj[N];
stack<int> st;
vector<vector<int> > comps;
int comp[N];
 
int dfs(int node , int par) {
    if(vis[node])
        return vis[node] == 1 ? low[node] : 1e9; // return low[node] if visited and in the same SCC , black / gray = gray
 
    dfsTime[node] = low[node] = Time++;
    vis[node] = 1;
    st.push(node);
 
    for (auto c : adj[node])
        if (c.first != par)
            low[node] = min(low[node] , dfs(c.first , node));
 
    if(low[node] == dfsTime[node]) { // the root of the SCC
        comps.push_back(vector<int>());
        do {
            vis[st.top()] = 2;     // we mark all the nodes of the current SCC as black
            comps.back().push_back(st.top());
            comp[st.top()] = comps.size();
            st.pop();
        } while(comps.back().back() != node);
    }
 
    return low[node];
}
 
vector<pair<int , int> > tree[N];
 
void tarjan() {
    for (int i = 1 ;i <= n ;i++)
        if(!vis[i])
            dfs(i , i);
 
 
    for (int i = 1 ;i <= n ;i++)
        for (auto c : adj[i])
            if (comp[i] != comp[c.first])
                tree[comp[i]].push_back({comp[c.first] , c.second});
}
 
 
 
 
pair<long long, int> farthest(int node , int par) {
    pair<long long , int> ret = {0 , node};
    for (auto c : tree[node]) {
        if (c.first == par) continue;
        auto p = farthest(c.first , node);
        p.first += c.second;
        ret = max(ret , p);
    }
    return ret;
}
 
vector<pair<int , long long> > sec;
void path(int from , int to , int par , long long dist) {
    sec.push_back({from , dist});
    if (from == to) {
        long long mn = sec.back().second;
        int theOne = sec.back().first;
 
        long long d = 0;
        for (int i = sec.size() - 2 ;i >= 0 ;i--) {
            d += sec[i + 1].second - sec[i].second;
            if (max(d , sec[i].second) < mn) {
                mn = max(d , sec[i].second) ;
                theOne = *min_element(comps[sec[i].first - 1].begin() , comps[sec[i].first - 1].end());
            }
            else if (max(d , sec[i].second) == mn)
                theOne = min(theOne , *min_element(comps[sec[i].first - 1].begin() , comps[sec[i].first - 1].end()));
        }
 
        printf("%d %lld\n" , theOne , mn);
        return;
    }
 
    for (auto &c : tree[from])
        if (c.first != par)
            path(c.first , to , from , dist + c.second);
 
    sec.pop_back();
}
 
void go() {
    int a = farthest(1 , -1).second;
    int b = farthest(a , -1).second;
    path(a , b , -1 , 0);
}
 
 
void init() {
    fill(adj , adj + (n + 1) , vector<pair<int , int>>());
    fill(tree , tree + (n + 1) , vector<pair<int , int>>());
    comps.clear();
    memset(vis , 0 , (n + 1) * sizeof vis[0]);
    memset(low  , 0 , (n + 1) * sizeof low[0]);
    memset(dfsTime , 0 , (n + 1) * sizeof dfsTime[0]);
    sec.clear();
    Time = 1;
}
 
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r"  ,stdin);
#endif
    int t ;
    scanf("%d" , &t);
    while (t--) {
        scanf("%d%d" , &n , &m);
 
        init();
        int u , v , c;
        while (m--) {
            scanf("%d%d%d" , &u , &v , &c);
            adj[u].push_back({v , c});
            adj[v].push_back({u , c});
        }
        tarjan();
 
        go();
    }
}