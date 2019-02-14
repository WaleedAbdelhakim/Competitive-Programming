#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second
#define INF 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define MASK bitset<17>

using namespace std;

typedef vector<int> vi;
typedef long long   ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 17 , M = (1 << N) + 5;
int n;
pair<int , int> arr[N];

double memo[M];
double D[N][N];

double solve(int msk){
    if(msk == 0)
        return 0;

    double &ret = memo[msk];
    if(ret == ret)
        return ret;

    ret = INF;

    int p1 , p2;
    for(p1 = 0 ;p1 < n*2 ;p1++)
        if(msk & (1 << p1))
            break;
    for(p2 = p1+1 ;p2 < n*2 ;p2++){
        if(msk & (1 << p2)){
            int t = msk;
            t &= ((1 << n*2)-1)^(1 << p2);
            t &= ((1 << n*2)-1)^(1 << p1);
            ret = min(ret , solve(t) + D[p1][p2]);
        }
    }

    return ret;
}
int main(){
    int test = 1;
    while(scanf("%d",&n) == 1 && n != 0){
        for(int i = 0 ;i < 2*n ;i++)
            scanf("%*s%d%d",&arr[i].f,&arr[i].s);

        for(int i = 0 ;i < 2*n ;i++)
            for(int j = i+1 ;j < 2*n ;j++)
                D[i][j] = hypot(arr[i].f - arr[j].f , arr[i].s - arr[j].s);

        memset(memo , -1 , sizeof memo);
        printf("Case %d: %.2f\n",test++,solve((1 << n*2) - 1));
    }

}
