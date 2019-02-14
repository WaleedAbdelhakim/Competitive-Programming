#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 1e9
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef unsigned long long  ll;

int dx[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dy[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 66 , M = 105;
int n , k;
ll memo[N][M][N];

ll solve(int i ,int rem ,int ones){
    if(i == n)
        return rem == 0 && ones == n / 2;

    ll &ret = memo[i][rem][ones];
    if(~ret)
        return ret;

    ret = 0;
    if(ones < n / 2)
        ret = solve(i+1 , ((rem % k) + ((ll(1) << i) % k))%k , ones+1);

    if(i != n-1)
        ret += solve(i+1 , rem , ones);
    return  ret;
}
int main(){
    int T ;
    scanf("%d",&T);
    for(int i = 1 ;i <= T ;i++){
        scanf("%d%d",&n,&k);
        if(n&1 || k == 0){
            printf("Case %d: %d\n",i,0);
            continue;
        }
        memset(memo , -1 , sizeof memo);
        cout << "Case " << i << ": " << solve(0 , 0 , 0) << endl;
    }
}
