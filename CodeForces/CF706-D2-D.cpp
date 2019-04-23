#include <bits/stdc++.h>

using namespace std;

struct trie {
    vector<vector<int> > v;
    vector<int> count;

    trie () {
        v.push_back(vector<int>(2 , -1));
        count.push_back(0);
    }

    void insert (string &s) {
        int cur = 0;
        for (int i = 0 ;i < s.size() ;i++) {
            if (v[cur][s[i] - '0'] == -1) {
                v[cur][s[i] - '0'] = v.size();
                v.push_back(vector<int>(2 , -1));
                count.push_back(0);
            }
            cur = v[cur][s[i] - '0'];
            count[cur]++;
        }
    }

    void del(string &s) {
        int cur = 0;
        for (int i = 0 ;i < s.size() ;i++) {
            cur = v[cur][s[i] - '0'];
            count[cur]--;
        }
    }

    int query(string &s) {
        int cur = 0 , ret = 0;
        for (int i = 0 ;i < s.size() ;i++) {
            int digit = s[i] - '0';
            if (v[cur][!digit] != -1 && count[v[cur][!digit]]) {
                ret += 1 << (30 - i);
                cur = v[cur][!digit];
            } else {
                cur = v[cur][digit];
            }
        }
        return ret;
    }
};

string bit_string(int x) {
    string ret = "";
    for (int i = 30 ;i >= 0 ;i--)
        ret += (x & (1 << i)) ? "1" : "0";
    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int q;
    scanf("%d", &q);
    trie t;
    string s = bit_string(0);
    t.insert(s);
    char op;
    int x;
    while (q--) {
        scanf(" %c %d" , &op , &x);
        string s = bit_string(x);
        if (op == '+')
            t.insert(s);
        else if (op == '-')
            t.del(s);
        else
            printf("%d\n" , t.query(s));
    }
}