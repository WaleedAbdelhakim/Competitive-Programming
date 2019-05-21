#include <bits/stdc++.h>

using namespace std;

const int N = 105;
int memo[N][N];

int solve (int n , int m) {
    if (!n || !m) return 1;
    int &ret = memo[n][m];
    if (~ret) return ret;
    return ret = min((int)1e9 , solve(n - 1 , m) + solve(n , m - 1));
}

string go(int n , int m , int k) {
    if (!m || !n) return string(n ? n : m , n ? 'a' : 'z');
    if (solve(n - 1 , m) >= k) return "a" + go(n - 1 , m , k);
    return "z" + go(n , m - 1 , k - solve(n -1 , m));
}

class TheDictionary {
public:
    string find(int n, int m, int k) {
        memset(memo , -1 , sizeof memo);
        return solve(n , m) >= k ? go(n , m , k) : "";
    }
};


