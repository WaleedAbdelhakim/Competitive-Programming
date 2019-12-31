#include <bits/stdc++.h>

using namespace std;

const int N = 31;
int memo[N] , memo2[N];

int solve(int n);

int go(int n) {
    if (n < 0) return 0;
    int &ret = memo2[n];
    if (~ret) return ret;
    return ret = solve(n) + go(n - 2);
}

int solve (int n) {
    if (n <= 0) return n == 0;
    int &ret = memo[n];
    if (~ret) return ret;
    return ret = 3 * solve(n - 2) + 2 * go(n - 4);
}

int main() {
    ios::sync_with_stdio(0) ,  cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int n;
    memset(memo , -1 , sizeof memo);
    memset(memo2 , -1 , sizeof memo2);
    while (cin >> n , ~n)
        cout << solve(n) << '\n';
}