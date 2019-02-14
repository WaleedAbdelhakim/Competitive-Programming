#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;

struct UnionFind{
    vi papa , r ;
    int f;
    UnionFind(int n){
        f = n;
        papa = r = vi(n+1);
        for(int i = 1 ;i < n ;i++)
            papa[i] = i , r[i] = 0;
    }

    int Find(int node){
        if(papa[node] == node)
            return node;

        return papa[node] = Find(papa[node]);
    }

    void Union(int a , int b){
        int p1 = Find(a) , p2 = Find(b);
        if(p1 != p2){
            f--;
            if(r[p1] > r[p2])
                swap(p1 , p2);
            papa[p1] = p2;
            if(r[p1] == r[p2])
                r[p2]++;
        }
    }
};
int main(){
    int n , m , T = 1;
    while(scanf("%d%d",&n,&m) && !(n == 0 && m == 0)){
        UnionFind uf(n);
        int a , b;
        while(m--){
            scanf("%d%d",&a,&b);
            uf.Union(a , b);
        }
        printf("Case %d: %d\n",T++ , uf.f);
    }
}
