#include <bits/stdc++.h>

using namespace std;

const int N = 55;
int memo[N];

class MessageMess {
    set<string> d;
    string s;
    int solve (int i) {
        if (i == s.size())
            return 1;

        int &ret = memo[i];
        if (~ret)
            return ret;

        ret = 0;

        string cur = "";
        for (int j = i ;j < s.size() ;j++) {
            cur += s[j];
            if (d.find(cur) != d.end())
                ret += solve(j + 1);
        }

        return ret = min(ret , 2);
    }

    string path(int i) {
        if (i == s.size())
            return "";

        string cur = "";
        for (int j = i ;j < s.size() ;j++) {
            cur += s[j];
            if (d.find(cur) != d.end() && solve(j + 1))
                return (i == 0 ? "" : " ") + cur + path(j + 1);
        }
    }

public:
    string restore(vector <string> dictionary, string message) {
        s = message;
        for (string s : dictionary) d.insert(s);
        memset(memo , -1 , sizeof memo);
        if (!solve(0))
            return "IMPOSSIBLE!";
        else if (solve(0) > 1)
            return "AMBIGUOUS!";

        return path(0);
    }

};
