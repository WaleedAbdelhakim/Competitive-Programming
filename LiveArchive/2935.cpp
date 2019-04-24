#include <bits/stdc++.h>

using namespace std;

string get(int l , int r , string &s) {
    if (r < l)
        return "()";

    vector<string> info;
    int d = 0 , first = l + 1;
    for (int i = l ;i <= r ;i++) {
        d += s[i] == '1';
        d -= s[i] == '0';
        if (!d) {
            info.push_back(get(first , i - 1 , s));
            first = i + 2;
        }
    }

    sort(info.begin() , info.end());

    string ret = "";
    for (string ss : info)
        ret += ss;

    return "(" + ret + ")";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    string a, b;
    cin >> T;
    while (T--) {
        cin >> a >> b;
        puts(get(0, a.size() - 1, a) == get(0, b.size() - 1, b) ? "same" : "different");
    }
}