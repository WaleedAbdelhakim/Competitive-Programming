#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 5 , MOD = 998244353;
int a , b , c;

int memo[N][N];

int mul(int a , int b) {
    return a * 1ll * b % MOD;
}

int solve(int i , int j) {
    if (i == 0) return 1;
    int &ret = memo[i][j];
    if (~ret) return ret;
    ret = solve(i - 1 , j);
    if (j) ret += mul(j , solve(i - 1 , j - 1));
    while (ret >= MOD) ret -= MOD;
    return ret;
}



int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    scanf("%d%d%d" , &a , &b , &c);
    memset(memo , -1 , sizeof memo);
    printf("%d" , mul(mul(solve(a , b) , solve(a , c)) , solve(b , c)));
}