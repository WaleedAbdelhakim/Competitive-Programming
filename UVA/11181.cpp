#include <bits/stdc++.h>

using namespace std;

const int N = 21;
double memo[N][N] , p[N];
int n;

double solve (int i , int rem) {
    if (i == n)
        return !rem;

    double &ret = memo[i][rem];
    if (ret == ret)
        return ret;

    ret = (1 - p[i]) * solve(i + 1 , rem);
    if (rem)
        ret += p[i] * solve(i + 1 , rem - 1);

    return ret;
}

void run(int n , int x) {
    ::n = n;

    for (int i = 0 ;i < n ;i++)
        cin >> p[i];

    memset(memo , -1 , sizeof memo);
    double xp = solve(0 , x);
    for (int i = 0 ;i < n ;i++) {
        double ans = 0;

        if (x != 0) {
            memset(memo , -1 , sizeof memo);
            swap(p[i] , p[0]);
            ans = (p[0] * solve(1 , x - 1)) / xp;
        }

        cout << fixed << setprecision(6) << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);

    int n , x , t = 1;
    while (cin >> n >> x , n + x) {
        cout << "Case " << t++ << ":\n";
        run(n , x);
    }
}
