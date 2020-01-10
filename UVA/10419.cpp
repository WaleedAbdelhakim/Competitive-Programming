#include <bits/stdc++.h>

using namespace std;

vector<int> v = {2};

const int N = 1e3 + 5 , M = 130 , K = 15;
int memo[N][M][K];

bool solve (int n , int i , int rem) {
    if (n <= 0 || i == v.size() || !rem)
        return n == 0 && rem == 0;

    int &ret = memo[n][i][rem];
    if (~ret)
        return ret;

    return ret = max(solve(n - v[i] , i + 1 , rem - 1) , solve(n , i + 1 , rem));
}

void path(int n , int i , int rem) {
    if (n == 0)
        return;

    if (solve(n - v[i] , i + 1 , rem - 1)) {
        cout << v[i];
        cout << (v[i] == n ? '\n' : '+');
        return path(n - v[i] , i + 1 , rem - 1);
    }

    path(n , i + 1 , rem);
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif

    auto prime = [](int n) {
        for (int i = 2 ;i < n ;i++)
            if (n % i == 0)
                return 0;
        return 1;
    };

    for (int i = 3 ;i < 300 ;i++)  {
        if (prime(i)) {
            v.push_back(i);
            v.push_back(i);
        }
    }

    sort(v.begin() , v.end() , [&](int i , int j) {
        return to_string(i) < to_string(j);
    });

    memset(memo , -1 , sizeof memo);

    int n , t , test = 1;
    while (cin >> n >> t , n || t) {
        cout << "CASE " << test++ << ":\n";
        if (solve(n , 0 , t))
            path(n , 0 , t);
        else
            cout << "No Solution.\n";
    }

}