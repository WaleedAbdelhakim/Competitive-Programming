#include <bits/stdc++.h>

using namespace std;

const int N = 305 , MOD = 1e9;
char s[N];
int memo[N][N] , vis[N][N] , vid;

int add (int a , int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
    return a;
}

int mul(int a , int b) {
    return (a * 1ll * b) % MOD;
}

int solve (int l , int r) {
    if (l == r || s[l] != s[r])
        return s[l] == s[r];

    int &ret = memo[l][r];
    if (vis[l][r] == vid)
        return ret;

    vis[l][r] = vid;
    ret = 0;    

    for (int i = l + 1 ;i < r ;i++)
        ret = add(ret , mul(solve(l + 1 , i) , solve(i + 1 , r)));

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    while (scanf("%s" , s) == 1)
        ++vid , printf("%d\n" , solve(0 , strlen(s) - 1));
}