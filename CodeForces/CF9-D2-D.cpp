#include <bits/stdc++.h>

using namespace std;

const int N = 36;
int n, h;
long long memo[N][N][2];

long long solve(int sz, int dep, bool b) {
    if (!sz)
        return b;
    if (sz == 1)
        return b ? (dep >= h) : (dep < h);

    long long &ret = memo[sz][dep][b];
    if (~ret)
        return ret;

    sz--;

    ret = 2 * solve(sz , dep + 1 , b);

    for (int i = 1; i < sz; i++) {
        if (b) {
            ret += solve(i, dep + 1, 1) * solve(sz - i, dep + 1, 1);
            ret += solve(i, dep + 1, 1) * solve(sz - i, dep + 1, 0);
            ret += solve(i, dep + 1, 0) * solve(sz - i, dep + 1, 1);
        } else {
            ret += solve(i, dep + 1, 0) * solve(sz - i, dep + 1, 0);
        }
    }

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    scanf("%d%d", &n, &h);
    memset(memo, -1, sizeof memo);
    printf("%lld", solve(n, 1, 1));
}