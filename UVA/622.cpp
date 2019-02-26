#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define val first
#define ind second

string s, allowed = "()*+";
string erorr[] = {"()" , ")(" , "(+" , "+)" , "(*" , "*)" , "+*" , "*+"};

bool valid() {
    int opened = 0 , first = 1;
    for (int i = 0; i < s.size(); i++) {
        opened += s[i] == '(';
        opened -= s[i] == ')';

        if (i + 1 < s.size()) {
            string t = s.substr(i , 2);
            for (int j = 0 ;j < 8 ;j++) if (t == erorr[j]) return 0;
            if (isdigit(s[i]) && s[i + 1] == '(') return 0;
            if (isdigit(s[i + 1]) && s[i] == ')') return 0;
        }

        if (!isdigit(s[i]) && allowed.find(s[i]) == -1) return 0;
        if (opened < 0) return 0;
        if (s[i] == '0' && first && i + 1 < s.size() && isdigit(s[i + 1])) return 0;
        first = !isdigit(s[i]);
    }

    return opened == 0;
}

pair<ll, int> evaluate(int i) {
    int st = i;
    ll total = 0, pro = 1 , temp;
    while (s[i] != ')') {
        temp = 0;
        int cnt = 0;
        while (isdigit(s[i])) {
            cnt++;
            temp = temp * 10 + s[i] - '0';
            i++;
        }

        if (cnt) pro *= temp;

        if (s[i] == '(') {
            auto c = evaluate(i + 1);
            pro *= c.val;
            i = c.ind;
        }

        if (s[i] == '+'){
            total += pro;
            pro = 1;
        }

        i += s[i] != ')';
    }
    return {total + pro , i + 1};
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    cin >> T;
    while (T--) {
        cin >> s;
        s = "(" + s + ")";

        if (!valid()) {
            cout << "ERROR\n";
            continue;
        }

        cout << evaluate(1).val << '\n';
    }
}