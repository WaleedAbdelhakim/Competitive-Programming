#include <bits/stdc++.h>
#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
using namespace std;

typedef vector<int> vi;
typedef long long ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1, -1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 2005;
int n , m , t;
int forest[N][N];
int memo[N][N][2];

int solve(int tree , int h ,bool jumped) {
    if(h <= 0 || tree >= n)
        return 0;

    int &ret = memo[tree][h][jumped];
    if(~ret)
        return ret;

    ret = 0;
    if(jumped)
        ret = max(ret , solve(tree + 1 , h , 1));

    return ret = max(ret , max(solve(tree , h - 1 , 0) , solve(0 , h - t , 1)) + forest[tree][h]);
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    scanf("%d",&T);

    while(T--) {
        scanf("%d%d%d",&n,&m,&t);

        memset(forest , 0 , sizeof forest);

        int x;
        for (int i = 0 ;i < n ;i++) {
            scanf("%d",&x);

            int h;
            while(x--) {
                scanf("%d",&h);
                forest[i][h]++;
            }
        }

        memset(memo , -1 , sizeof memo);
        printf("%d\n" , solve(0 , m , 1));
    }
}