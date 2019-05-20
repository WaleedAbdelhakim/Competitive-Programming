#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
double ans[N];

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    double p = 1;
    for (int i = 2 ;i < N ;i += 2) {
        p *= i - 1;
        p /= i;
        ans[i] = 1 - p;
    }

    int n , x;
    cin >> n;
    while (n--) {
        cin >> x;
        cout << fixed << setprecision(4) << ans[x - 2] << endl;
    }
}