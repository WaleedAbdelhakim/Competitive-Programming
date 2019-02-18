#include <bits/stdc++.h>

using namespace std;

const int N = 705;
int n;
int arr[N] , memo[N][N][2];

bool can (int l , int r , bool b) {
    if (r < l)
        return 1;
    int parInd = b ? r + 1 : l - 1;
    if (l == r)
        return __gcd(arr[l] , arr[parInd]) > 1;

    int &ret = memo[l][r][b];
    if (~ret)
        return ret;

    for (int i = l ;i <= r ;i++)
        if (__gcd(arr[i] , arr[parInd]) > 1 && can(l , i - 1 , 1) && can(i + 1 , r , 0))
            return ret = 1;

    return ret = 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    scanf("%d" , &n);
    for (int i = 0 ;i < n ;i++)
        scanf("%d" , arr + i);

    memset(memo , -1 , sizeof memo);
    puts(can(0 , n - 1 , 1) ? "Yes" : "No");
}

