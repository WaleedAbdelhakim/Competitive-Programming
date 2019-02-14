#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 10;
int n , d , m;

vector<pair<int , int> > adj[N];

int go(int staion ,int *dest ,int on_board = 0 , int money = 0){
    if(staion == d)
        return money;

    int t = dest[staion];
    on_board -= t;
    dest[staion] = 0;

    int ret = go(staion+1 , dest , on_board , money + on_board);
    for(int i = 1 ;i < (1 << adj[staion].size()) ;i++){
        for(int j = 0 ;j < adj[staion].size() ;j++){
            if(i & (1 << j)){
                on_board += adj[staion][j].second;
                dest[adj[staion][j].first] += adj[staion][j].second;
            }
        }
        if(on_board <= n)
            ret = max(ret , go(staion+1 , dest , on_board , money + on_board));

        for(int j = 0 ;j < adj[staion].size() ;j++){
            if(i & (1 << j)){
                on_board -= adj[staion][j].second;
                dest[adj[staion][j].first] -= adj[staion][j].second;
            }
        }
    }

    dest[staion] = t;
    return ret;
}
int main(){
    while(scanf("%d %d %d" ,&n ,&d ,&m) , (n || d || m)){
        for(int i = 0 ;i < N ;i++)
            adj[i].clear();
        int f , t , c;
        while(m--){
            scanf("%d%d%d",&f,&t,&c);
            adj[f].pb({t , c});
        }
        int *dest = new int[N];
        for(int i = 0 ;i < N ;i++)
            dest[i] = 0;
        printf("%d\n",go(0 , dest));
    }
}
