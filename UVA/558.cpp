#include <bits/stdc++.h>
#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;

int dx[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dy[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

struct edge{
    int from , to , w;
};
int n , m , T;

bool detect(vector<edge> & info){
    vi d(n , inf);
    d[0] = 0;
    for(int i = 1 ;i <= n ;i++){
        bool change = 0;
        for(edge e : info){
            if(d[e.to] > d[e.from] + e.w){
                d[e.to] = d[e.from] + e.w;
                change = 1;
                if(i == n)
                    return true;
            }
        }
        if(!change)
            break;
    }
    return false;
}
int main(){
    int T;
    scanf("%d",&T);
    while(scanf("%d%d",&n,&m) == 2){
        int a , b , w;
        vector<edge> info;
        while(m--){
            scanf("%d%d%d",&a,&b,&w);
            info.pb({a , b , w});
        }
        puts(detect(info) ? "possible" : "not possible");
    }

}
