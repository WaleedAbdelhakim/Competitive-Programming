#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

struct Edge{
    int f , t , w;
    bool operator <(const Edge &other) const{
        return w > other.w;
    }
};
struct DSU{
    vi parent , r;
    DSU(int n) : parent(n) ,r(n){
        for(int i = 0 ;i < n ;i++)
            parent[i] = i , r[i] = 0;
    }

    int Find(int node){
        return node == parent[node] ? node : parent[node] = Find(parent[node]);
    }

    bool Union(int a , int b){
        a = Find(a);
        b = Find(b);
        if(r[a] > r[b])
            swap(a , b);
        parent[a] = b;
        if(r[a] == r[b])
            r[b]++;
    }

    bool sameSet(int a , int b){
        return Find(a) == Find(b);
    }
};
int main(){
    int T , n , m;
    scanf("%d",&T);

    for(int i = 1 ;i <= T ;i++){
        scanf("%d%d",&n,&m);

        DSU dsu(n);
        vector<Edge> edges;
        int a , b , w;
        while(m--){
            scanf("%d%d%d",&a,&b,&w);
            edges.pb({a , b , w});
        }

        sort(all(edges));

        int mn = inf;
        for(auto &x : edges){
            if(!dsu.sameSet(x.f , x.t)){
                dsu.Union(x.f , x.t);
                mn = min(mn , x.w);
            }
        }

        printf("Case #%d: %d\n",i , mn);
    }
}
