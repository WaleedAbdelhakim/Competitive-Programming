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

struct point{
    double x , y;
};

const int N = 100 + 5;
int n;
point arr[N];


double prim(){
    bool vis[N] = {0};
    priority_queue<pair<double , int> > pq;
    pq.push({0 , 0});

    double MST = 0;
    while(pq.size()){
        auto cur = pq.top();
        pq.pop();

        if(vis[cur.second])continue;
        vis[cur.second] = 1;

        MST += -cur.first;


        for(int i = 0 ;i < n ;i++){
            if(!vis[i]){
                double dist =  hypot((arr[i].x - arr[cur.second].x) ,(arr[i].y - arr[cur.second].y));
                pq.push({-dist , i});
            }
        }
    }

    return MST;
}
int main(){
    int T;
    scanf("%d",&T);
    for(int i = 0 ;i < T ;i++){
        if(i != 0)
            putchar('\n');
        scanf("%d",&n);
        for(int i = 0 ;i < n ;i++)
            cin >> arr[i].x >> arr[i].y;

        printf("%.2f\n" , prim());
    }
}
