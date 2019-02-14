#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 33;
int t , w , n;
int d[N] , v[N];
int memo[N][1005];
int solve(int i ,int rem){
    if(i == n)
        return 0;

    int &ret = memo[i][rem];
    if(~ret)
        return ret;

    ret = solve(i+1 , rem);
    if(3*d[i]*w <= rem)
        ret = max(ret , solve(i+1 , rem - 3*d[i]*w) + v[i]);

    return ret;
}

vi path;
void findPath(int i ,int rem){
    if(i == n)
        return;

    int f = solve(i+1 , rem);
    int s = solve(i+1 , rem - 3*d[i]*w) + v[i];

    if(s > f){
        path.pb(i);
        findPath(i+1 , rem - 3*d[i]*w);
    }else
        findPath(i+1 , rem);
}
int main(){
    bool f = 1;
    while(scanf("%d%d%d",&t,&w,&n) == 3){
        if(!f)
            puts("");
        else  f = 0;

        for(int i = 0 ;i < n ;i++)
            scanf("%d%d",&d[i] ,&v[i]);

        path.clear();
        memset(memo , -1 , sizeof memo);
        printf("%d\n",solve(0 , t));
        findPath(0 , t);

        printf("%d\n",path.size());
        for(int x : path)
            printf("%d %d\n",d[x],v[x]);

    }
}
