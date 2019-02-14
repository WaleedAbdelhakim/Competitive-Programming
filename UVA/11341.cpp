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

const int N = 12 , M = 105;
int n , m;

int t[N][N];

int memo[N][M];
int solve(int i ,int rem){
    if(i == n)
        return 0;

    int &ret = memo[i][rem];
    if(ret != -1)
        return ret;

    ret = -INF;
    for(int j = 5 ;j <= 10;j++){
        if(t[i][j] != -1 && rem >= t[i][j]){
            int sub = solve(i+1 , rem - t[i][j]);
            if(sub != -INF)
                ret = max(ret , sub + j);
        }
    }

    return ret;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);

        memset(t , -1 , sizeof t);

        int x;
        for(int i = 0 ;i < n ;i++){
            for(int j = 1 ;j <= m ;j++){
                scanf("%d",&x);
                if(t[i][x] == -1)
                    t[i][x] = j;
            }
        }

        memset(memo , -1 , sizeof memo);
        int ans = solve(0 , m);

        if(ans == -INF)
            puts("Peter, you shouldn't have played billiard that much.");
        else
            printf("Maximal possible average mark - %.2f.\n",double(ans) / n + 1e-9);
    }
}

