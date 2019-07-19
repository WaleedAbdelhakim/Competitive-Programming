#include <bits/stdc++.h>

using namespace std;

int f[2][26];

struct trie {
    vector<vector<int> > v;
    vector<bool> leaf;

    trie () {
        v.push_back(vector<int>(26 , -1));
        leaf.push_back(0);
    }

    int insert (string &s , bool b) {
        int cur = 0 , cnt = 0;
        for (int i = 0 ;i < s.size() ;i++) {
            if (v[cur][s[i] - 'a'] == -1) {
                cnt++;
                f[b][s[i] - 'a'] += i != 0;
                v[cur][s[i] - 'a'] = v.size();
                v.push_back(vector<int>(26 , -1));
                leaf.push_back(0);
            }
            cur = v[cur][s[i] - 'a'];
        }
        leaf[cur] = 1;
        return cnt;
    }
};


int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
    int n , m;
    while (cin >> n >> m , n + m) {
        memset(f , 0 , sizeof f);

        trie pre , suff;
        string s;

        int prefixes = 0 , suffixes = 0;
        while (n--) {
            cin >> s;
            prefixes += pre.insert(s , 0);
        }

        while (m--) {
            cin >> s;
            reverse(s.begin() , s.end());
            suffixes += suff.insert(s , 1);
        }

        long long all = prefixes * 1ll * suffixes;
        for (int i = 0 ;i < 26 ;i++)
            all -= f[0][i] * 1ll * f[1][i];

        cout << all << '\n';
    }
}