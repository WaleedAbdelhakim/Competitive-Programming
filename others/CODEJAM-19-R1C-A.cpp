#include <bits/stdc++.h>

using namespace std;

string moves = "RSP";
string rmoves = "PRS";

int get_ind(char c) {
    return moves.find(c);
}

int other(int i , int j) {
    for (int k = 0 ;k < 3 ;k++)
        if (k != i && k != j)
            return k;
}

char get_char(int x) {
    return moves[x];
}

char counter(char c) {
    return rmoves[moves.find(c)];
}

char winner(char a , char b) {
    if ((get_ind(a) + 1) % 3 == get_ind(b))
        return a;
    return b;
}

struct trie {
    vector<vector<int> > v;

    trie () {
        v.push_back(vector<int>(3 , -1));
    }

    void insert (string &s) {
        int cur = 0;
        for (int i = 0 ;i < s.size() ;i++) {
            if (v[cur][get_ind(s[i])] == -1) {
                v[cur][get_ind(s[i])] = v.size();
                v.push_back(vector<int>(3 , -1));
            }
            cur = v[cur][get_ind(s[i])];
        }
    }

    pair<bool , string> can() {
        int cur = 0;
        string ans = "";
        while (1) {
            int cnt = 0;
            for (int i = 0 ;i < 3 ;i++)
                cnt += v[cur][i] == -1;

            if (cnt == 0)
                return {0 , ":("};

            for (int i = 0 ;i < 3 ;i++) {
                for (int j = i + 1 ;j < 3 ;j++) {
                    if (v[cur][i] == -1 && v[cur][j] == -1) {
                        ans += counter(get_char(other(i , j)));
                        return {1 , ans};
                    }
                }
            }

            string op = "";
            for (int i = 0 ;i < 3 ;i++)
                if (v[cur][i] != -1)
                    op += get_char(i);

            char c = winner(op[0] , op[1]);
            ans += c;
            cur = v[cur][get_ind(c)];
        }
    }
};

void solve() {
    int n;
    cin >> n;

    int mx_len = n;
    vector<string> a(n);
    for (int i = 0 ;i < n ;i++) {
        cin >> a[i];
        mx_len = max(mx_len , (int)a[i].size());
    }

    trie t;
    for (int i = 0 ;i < n ;i++) {
        int sz = a[i].size();
        for (int j = 0 ; a[i].size() < mx_len ;j++)
            a[i].push_back(a[i][j]);
        t.insert(a[i]);
    }

    auto ans = t.can();
    if (ans.first)
        cout << ans.second;
    else
        cout << "IMPOSSIBLE";
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);

    int t;
    cin >> t;
    for (int i = 1 ;i <= t ;i++) {
        cout << "Case #" << i << ": ";
        solve();
        cout << '\n';
    }
}