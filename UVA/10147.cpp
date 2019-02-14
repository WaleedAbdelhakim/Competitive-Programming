#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 1e9
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;


double dist(pair<int,int> a ,pair<int,int> b){
    int x = a.first , y = a.second , x2 = b.first , y2 = b.second;
    return sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
}
struct UnionFind{
    vi papa , r;
    UnionFind(int n){
        papa = vi(n+1) , r = vi(n+1);
        for(int i = 0 ;i < n+1;i++)
            papa[i] = i , r[i] = 0;
    }

    int Find(int x){
        return x == papa[x] ? x : papa[x] = Find(papa[x]);
    }

    bool Union(int a , int b){
        a = Find(a) , b = Find(b);
        if(a != b){
            if(r[a] > r[b])
                swap(a , b);
            papa[a] = b;
            if(r[a] == r[b])
                r[b]++;
            return 1;
        }
        return 0;
    }
};
int main(){
    int T;
    scanf("%d",&T);
    int n , m;
    while(T--){
        scanf("%d",&n);
        UnionFind uf(n);
        pair<int , int> p[n];
        for(int i = 0 ;i < n ;i++)
            scanf("%d %d",&p[i].first ,&p[i].second);

        scanf("%d" ,&m);

        int a , b;
        while(m--){
            scanf("%d%d",&a,&b);
            uf.Union(a , b);
        }

        vector<pair<double , pair<int , int> > > info;

        for(int i = 0 ;i < n ;i++)
            for(int j = i + 1 ;j < n ;j++)
                info.pb({dist(p[i] , p[j]) , {i+1 , j+1}});

        sort(all(info));

        int added = 0;
        for(int i = 0 ;i < info.size() ;i++){
            int x = info[i].second.first , y = info[i].second.second;
            if(uf.Union(x , y)){
                printf("%d %d\n",x , y) , added++;
            }
        }
        if(!added)
            puts("No new highways need");

        if(T)
            putchar('\n');
    }


}
