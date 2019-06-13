#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
int factors[N];

void pf(int n, int add) {
    for (int i = 2; i * i <= n; i++) while (n % i == 0) n /= i, factors[i] += add;
    if (n != 1) factors[n] += add;
}

long long power(long long a, long long b) {
    if (!b) return 1;
    long long r = power(a, b / 2);
    r = r * r % 10;
    if (b & 1) return r * a % 10;
    return r;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    string s;
    while (cin >> s) {
        memset(factors, 0, sizeof factors);
        for (int i = 2; i <= s.size(); i++) pf(i, 1);
        int f[26] = {};
        for (char c : s) f[c - 'a']++;
        for (int i = 0; i < 26; i++) for (int j = 2; j <= f[i]; j++) pf(j, -1);
        factors[10] = 0;
        int sub = min(factors[2], factors[5]);
        factors[2] -= sub;
        factors[5] -= sub;
        int ans = 1;
        for (int i = 1; i <= s.size(); i++) ans = (ans * power(i, factors[i])) % 10;
        cout << ans << '\n';
    }
}