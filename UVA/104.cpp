#include <bits/stdc++.h>

using namespace std;

const int N = 25;
int n;
double m[N][N] , memo[N][N][N];

bool same(double a, double b) {
    return abs(a - b) < 1e-6;
}

double solve (int i , int j , int rem) {
    if (!rem)
        return m[i][j];

    double &ret = memo[i][j][rem];
    if (ret == ret)
        return ret;

    ret = -1e9;
    for (int k = 0 ;k < n ;k++)
        ret = max(ret , m[i][k] * solve(k , j , rem - 1));

    return ret;
}

void path(int i , int j , int rem) {
    if (!rem)
        return;

    double &ret = memo[i][j][rem];

    for (int k = 0 ;k < n ;k++) {
        if (same(ret , m[i][k] * solve(k , j , rem - 1))) {
            cout << k + 1 << ' ';
            return path(k , j , rem - 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    while (cin >> n) {
        for (int i = 0 ;i < n ;i++){
            for (int j = 0 ;j < n ;j++) {
                if (i != j) {
                    cin >> m[i][j];
                }
                else
                    m[i][j] = 1;
            }
        }

        memset(memo , -1 , sizeof memo);

        bool good = 0;
        for (int len = 1 ; !good && len <= n - 1  ;len++) {
            for (int i = 0 ;i < n ;i++) {
                if (solve(i , i , len) > 1.01 || same(solve(i , i , len) , 1.01)) {
                    cout << i + 1 << ' ';
                    path(i , i , len);
                    cout << i + 1 << '\n';
                    good = 1;
                    break;
                }
            }
        }

        if (!good)
            cout << "no arbitrage sequence exists\n";
    }
}