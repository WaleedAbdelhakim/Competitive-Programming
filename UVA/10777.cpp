#include <bits/stdc++.h>

using namespace std;

void run() {
    int n;
    cin >> n;

    bool pos = 0;
    double a = 0 , b = 1;
    for (int i = 0 ;i < n ;i++) {
        int x;
        double p;
        cin >> x >> p;

        a += abs(x) * p;

        if (x < 0)
            b -= p;
        else
            pos = 1;
    }

    if (!pos)
        cout << "God! Save me\n";
    else
        cout << fixed << setprecision(2) << a / b << '\n';
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int t;
    cin >> t;

    for (int i = 1 ;i <= t ;i++) {
        cout << "Case " << i << ": ";
        run();
    }
}
