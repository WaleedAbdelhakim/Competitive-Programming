#include <bits/stdc++.h>
#define pb push_back
#define INF 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;

int dx[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dy[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 105;
int n;

vector<vi> adj , radj;
bool cycle[N] = {0} , vis[N] = {0};
int energy[N];

bool dfs(int node){
    if(cycle[node])
        return 1;

    vis[node] = 1;

    bool ret = 0;
    for(int child : radj[node])
        if(!vis[child])
            ret |= dfs(child);

    return ret;
}
bool bellman(){
    vi d(n+1 , -INF);
    memset(cycle , 0 , sizeof cycle);
    memset(vis , 0 , sizeof vis);

    d[1] = 100;
    for(int i = 1 ;i <= n ;i++){
        bool noChange = 1;
        for(int j = 1 ;j <= n ;j++){
            for(int child : adj[j]){
                if(d[child] < d[j] + energy[child] && d[j] + energy[child] > 0){
                    d[child] = d[j] + energy[child];
                    noChange = 0;

                    if(i == n)
                        cycle[child] = 1;
                }
            }
        }
        if(noChange)
            break;
    }
    return (d[n] > 0 || dfs(n));
}
int main(){
    while(scanf("%d",&n) == 1 && n != -1){
        adj.resize(n+1);
        radj.resize(n+1);

        for(int i = 1 ;i <= n ;i++){
            int m;
            scanf("%d%d",&energy[i],&m);

            int child;
            while(m--){
                scanf("%d",&child);
                adj[i].pb(child);
                radj[child].pb(i);
            }
        }

        puts(bellman()? "winnable" : "hopeless");

        adj.clear();
        radj.clear();
    }
}
