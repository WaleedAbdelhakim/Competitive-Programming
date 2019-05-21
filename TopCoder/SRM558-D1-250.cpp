#include <bits/stdc++.h>

using namespace std;

const int N = 55;
int memo[N][4] , vis[N][4] , vid = 1, len;
string s;

int solve (int i , int last) {
    if (i == s.size())
        return 0;

    int &ret = memo[i][last];
    if (vis[i][last] == vid)
        return ret;

    vis[i][last] = vid;
    ret = 1e9;

    bool cr = 1 , cg = 1 , cb = 1;
    for (int j = i ;j < i + len && (cr + cg + cb) ;j++) {
        cr &= s[j] == '*' || s[j] == 'R';
        cg &= s[j] == '*' || s[j] == 'G';
        cb &= s[j] == '*' || s[j] == 'B';
        if (cr && last == 0) ret = min(ret , solve(j + 1 , 0) + 1);
        if (cg && last == 1) ret = min(ret , solve(j + 1 , 1) + 1);
        if (cb && last == 2) ret = min(ret , solve(j + 1 , 2) + 1);
    }

    if (cr) ret = min(ret , solve(i + len , 0) + 1);
    if (cg) ret = min(ret , solve(i + len , 1) + 1);
    if (cb) ret = min(ret , solve(i + len , 2) + 1);

    return ret;
}

class Stamp {
public:
    int getMinimumCost(string ss, int stampCost, int pushCost) {
        s = ss;
        long long mn = 1e11;
        for (len = 1 ;len <= s.size() ;len++ , vid++)
            mn = min(mn , len * stampCost + solve(0 , 3) * 1ll * pushCost);
        return mn;
    }
};

