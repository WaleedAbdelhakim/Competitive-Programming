#include <bits/stdc++.h>

using namespace std;

const int N = 4e5 + 5;
int n , m;
int vis[N] , low[N] , dfsTime[N] , Time;
vector<pair<int , int> > adj[N];
stack<int> st;
vector<vector<int> > comps;

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
            st.pop();
        } while(comps.back().back() != node);
    }

    return low[node];
}

vector<pair<int , pair<int , int> > > ans;

int comp[N] , vis_time[N] , t;
void go(int node , int par) {
    vis_time[node] = t++;
    for (auto &c : adj[node]) {
        int child = c.first;

        if (child == par || vis_time[child] > vis_time[node]) continue;

        if (~vis_time[child]) {
            ans.push_back({c.second , {node , child}});
            continue;
        }

        if (comp[node] == comp[child])
            ans.push_back({c.second , {node , child}});
        else
            ans.push_back({c.second , {child , node}});

        go(child , node);
    }
}

void tarjan() {
    for (int i = 1 ;i <= n ;i++)
        if(!vis[i])
            dfs(i , -1);


    int mx = 0 , theOne = -1;
    for (int i = 0 ;i < comps.size() ;i++) {
        for (int &x : comps[i])
            comp[x] = i;

        if (comps[i].size() > mx) {
            mx = comps[i].size();
            theOne = i;
        }
    }

    printf("%d\n" , mx);
    memset(vis_time , -1 , sizeof vis_time);
    go(comps[theOne].back() , -1);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r"  ,stdin);
#endif
    int m , a , b;
    scanf("%d%d" , &n , &m);
    for (int i = 0 ;i < m ;i++) {
        scanf("%d%d" , &a , &b);
        adj[a].push_back({b , i});
        adj[b].push_back({a , i});
    }

    tarjan();

    sort(ans.begin() , ans.end());

    for (auto &p : ans)
        printf("%d %d\n" , p.second.first , p.second.second);
}