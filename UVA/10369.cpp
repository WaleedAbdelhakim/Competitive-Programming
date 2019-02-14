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

const int N = 505;
int s , n;
int x[N] , y[N];

double prim(){
    bool vis[N] = {0};
    priority_queue<pair<double , int> > pq;

    vector<double> costs;
    pq.push({0 , 0});
    while(pq.size()){
        auto cur = pq.top();
        pq.pop();

        if(vis[cur.second]) continue;
        vis[cur.second] = 1;

        costs.pb(-cur.first);

        for(int i = 0 ;i < n ;i++){
            if(!vis[i]){
                double dist = hypot(x[cur.second] - x[i] , y[cur.second] - y[i]);
                pq.push({-dist , i});
            }
        }
    }

    sort(all(costs) , greater<double>());

    return costs[s-1];
}
int main(){
    int T;
    scanf("%d",&T);

    while(T--){
        scanf("%d %d",&s,&n);
        for(int i = 0 ;i < n ;i++)
            scanf("%d%d",&x[i] , &y[i]);


        printf("%.2f\n",prim());
    }
}
