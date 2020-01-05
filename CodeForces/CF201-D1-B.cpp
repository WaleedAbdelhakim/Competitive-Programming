#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
int n , m , a[N][N];

long long calc(int x , bool b) {
    long long ret = 0;
    for (int i = 0 ;i < n ;i++) {
        for (int j = 0 ;j < m ;j++) {
            int target = b ? j : i;
            long long d = abs(x - target) * 4ll;
            d += (target >= x ? 2 : -2);
            d *= d;
            ret += d * a[i][j];
        }
    }
    return ret;
}

pair<long long , int> ts(bool b , int lim) {
    int l = 0 , r = lim;
    while (r - l > 3) {
        int m1 = l + (r - l + 1) / 3;
        int m2 = r - (r - l + 1) / 3;
        long long f = calc(m1 , b);
        long long s = calc(m2 , b);
        if (s < f)
            l = m1 + 1;
        else
            r = m2 - 1;
    }

    long long ans = 1e18 , ind = -1;
    for (int i = l ;i <= r ;i++) {
        long long cur = calc(i , b);
        if (cur < ans) {
            ans = cur;
            ind = i;
        }
    }

    return {ans , ind};
}

int main() {
    ios::sync_with_stdio(0) ,  cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    cin >> n >> m;
    for (int i = 0 ;i < n ;i++)
        for (int j = 0 ;j < m ;j++)
            cin >> a[i][j];

    auto f = ts(0 , n) , s = ts(1 , m);
    cout << f.first + s.first << '\n' << f.second << ' ' << s.second;
}