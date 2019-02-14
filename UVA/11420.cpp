#include <bits/stdc++.h>
#include <math.h>
#define pb push_back
#define INF 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long   ll;

const int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
const int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 66;

ll memo[N][2][N];
ll solve(int i ,bool prev ,int ns){
    if(i < 0 || ns < 0)
        return 0;
    if(i == 0)
        return ns == 0;

    ll &ret = memo[i][prev][ns];
    if(ret != -1)
        return ret;

    return ret = solve(i-1 , 0 , ns - prev) + solve(i-1 , 1 , ns-1);
}
int main(){
    int n , m;

    memset(memo , -1 , sizeof memo);

    while(scanf("%d%d",&n,&m) , (n >= 0)){
        printf("%lld\n",solve(n , 0 , n - m));
    }
}
