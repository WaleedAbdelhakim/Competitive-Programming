#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;
string s , level[N];
int ind;

void go (int dep) {
    level[dep] += s[ind];
    if (isupper(s[ind--])) {
        go(dep + 1);
        go(dep + 1);
    }
}

void init() {
    ind = s.size() - 1;
    for (int i = 0 ;i < N ;i++)
        level[i] = "";
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> s;
        init();
        go(0);
        for (int i = N - 1 ;i >= 0 ;i--) cout << level[i];
        cout << '\n';
    }
}
