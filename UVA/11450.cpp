#include <bits/stdc++.h>
#define pb push_back
#define INF 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long   ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 22 , M = 205;
int T , m , c;
vector<vector<int> > arr;

int memo[N][M];

int solve(int i ,int rem){
    if(i == arr.size())
        return m - rem;

    int &ret = memo[i][rem];
    if(~ret)
        return ret;

    ret = -INF;
    for(int x : arr[i])
        if(x <= rem)
            ret = max(ret , solve(i+1 , rem - x));

    return ret;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&m,&c);
        arr.resize(c);

        int k , p;
        for(int i = 0 ;i < c ;i++){
            scanf("%d",&k);
            arr[i].resize(k);
            for(int j = 0 ;j < k ;j++)
                scanf("%d",&arr[i][j]);
        }

        memset(memo , -1,  sizeof memo);
        int r = solve(0 , m);
        if(r == -INF)
            puts("no solution");
        else
            printf("%d\n",r);

        arr.clear();
    }
}

