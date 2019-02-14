#include <bits/stdc++.h>
#define pb push_back
#define INF 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;

int dx[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dy[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};


int n;

struct edge{
    int from , to , w;
};

int cube(int val){
    return val * val * val;
}

vi bellman(vector<edge> & edgeList){
    vi d(n+1 , INF);
    d[1] = 0;

    for(int i = 1 ;i <= n ;i++){
        bool change = 0;
        for(auto e : edgeList){
            if(d[e.to] > d[e.from] + e.w && d[e.from] != INF){
                d[e.to] = d[e.from] + e.w;
                change = 1;
                if(i == n)
                    d[e.to] = -INF;
            }
        }
        if(!change)
            break;
    }
    return d;
}
int main(){
    int test = 1;
    while(scanf("%d",&n) == 1){
        int busyness[n];
        for(int i = 0 ;i < n ;i++)
            scanf("%d",busyness + i);

        int m , a , b , w , q;
        scanf("%d",&m);

        vector<edge> edgeList;

        while(m--){
            scanf("%d%d",&a,&b);
            w = cube(busyness[b-1] - busyness[a-1]);
            edgeList.pb({a , b , w});
        }

        vi d = bellman(edgeList);

        scanf("%d",&q);

        printf("Set #%d\n",test);

        int dest;
        while(q--){
            scanf("%d",&dest);
            if(d[dest] < 3 || d[dest] == INF)
                puts("?");
            else
                printf("%d\n",d[dest]);
        }

        test++;
        cin.get();
    }
}
