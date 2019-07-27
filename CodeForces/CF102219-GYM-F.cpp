#include <bits/stdc++.h>
 
 
using namespace std;
 
const int N = 2e3 + 5 , MOD = 1e9 + 7;
int bad[N][N] , memo[N][1 << 9];
int n, e;
 
int add (int a , int b) {
    a += b;
    while (a >= MOD)
        a -= MOD;
    return a;
}
 
int solve (int i , int msk) {
    if (i == n)
        return 1;
 
    int &ret = memo[i][msk];
    if (~ret)
        return ret;
 
    ret = 0;
 
    for (int j = e ;j >= 0 ;j--) {
        int dist = e - j;
        if (i - dist >= 0 && !(msk & (1 << j)) && !bad[i][i - dist]) {
            int nwmsk = msk | (1 << j);
            nwmsk >>= 1;
            ret = add(ret , solve(i + 1 , nwmsk));
        }
    }
 
    for (int j = e + 1 ;j <= 2 * e ;j++) {
        int dist = j - e;
        if (i + dist < n && !(msk & (1 << j)) && !bad[i][i + dist]) {
            int nwmsk = msk | (1 << j);
            nwmsk >>= 1;
            ret = add(ret , solve(i + 1 , nwmsk));
        }
    }
 
    return ret;
}
 
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int k;
    scanf("%d%d%d", &n, &e, &k);
 
    int a , b;
    while (k--) {
        scanf("%d%d" , &a , &b);
        bad[a - 1][b - 1] = 1;
    }
 
    memset(memo , -1 , sizeof memo);
 
    printf("%d" , solve(0 , 0));
}