#include <bits/stdc++.h>

using namespace std;

int n , m;
string str;

const int N = 1 << 19 , M = 105;
long long memo[N][M] , p[19];
int ind[N];

long long solve (int i , int mask, int mod) {
    if (i == str.size())
        return mod == 0;

    long long &ret = memo[mask][mod];
    if (~ret)
        return ret;

    ret = 0;

    int vis = 0;
    for (int s = mask ; s ; s -= s&-s) {
        int j = ind[s&-s];
        int digit = str[j] - '0';
        if (!(vis & (1 << digit)) && (i != str.size() - 1 || digit)) {
            vis |= 1 << digit;
            ret += solve(i + 1 , mask ^ (1 << j) , (mod + digit * p[i]) % m);
        }
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    cin >> str >> m;

    ind[1] = 0;
    p[0] = 1;
    for (int i = 1 ;i < 19 ;i++)
        ind[1 << i] = i , p[i] = p[i - 1] * 10;

    memset(memo , -1 , sizeof memo);
    printf("%lld\n" , solve(0 , (1 << str.size()) - 1 , 0));
}