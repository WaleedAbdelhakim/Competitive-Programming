#include <bits/stdc++.h>
#include <math.h>
#define pb push_back
#define INF 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long   ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 1005 , M = 32;
int n;
int p[N] , w[N];

int memo[N][M];

int solve(int i ,int rem){
    if(i == n)
        return 0;

    int &ret = memo[i][rem];
    if(ret != -1)
        return ret;

    ret = solve(i+1 , rem);
    if(rem >= w[i])
        ret = max(ret , solve(i+1 , rem-w[i]) + p[i]);

    return ret;
}
int main(){
    int T ;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i = 0 ;i < n ;i++)
            scanf("%d%d",&p[i],&w[i]);

        int g , ans = 0 , mg;
        scanf("%d",&g);

        memset(memo , -1 , sizeof memo);
        while(g--){
            scanf("%d",&mg);
            ans += solve(0 , mg);
        }
        printf("%d\n",ans);
    }

}

