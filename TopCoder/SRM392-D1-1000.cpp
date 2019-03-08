#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

const int N = 20;
map<vi , bool> memo[N][2];
class EquiDigitNumbers {
    string s;
    bool valid (vi &v) {
        int len = *max_element(v.begin() , v.end()) * (v.size() - count(v.begin() , v.end() , 0));
        return len < N;
    }

    bool good(vi &v) {
        int mx = *max_element(v.begin() , v.end());
        for (int x : v)
            if (x != mx && x != 0)
                return 0;
        return 1;
    }

    int solve (int i , bool g , vi f) {
        if (!valid(f)) return 0;
        if (i < 0) return good(f);

        if (memo[i][g].count(f))
            return memo[i][g][f];

        bool &ret = memo[i][g][f];
        int l = g ? 0 : s[i] - '0';
        int mx = *max_element(f.begin() , f.end());

        for (int j = l ;j <= 9 ;j++) {
            if (j || mx) f[j]++;
            if (solve(i - 1 , g || (j > l) , f)) return ret = 1;
            if (j || mx) f[j]--;
        }

        return ret = 0;
    }

    string build (int i , bool g , vi f) {
        if (i < 0) return "";
        int l = g ? 0 : s[i] - '0';
        int mx = *max_element(f.begin() , f.end());

        for (int j = l ;j <= 9 ;j++) {
            if (j || mx) f[j]++;
            if (solve(i - 1 , g || (j > l) , f))
                return ((j || mx) ? string(1 , char(j + '0')) : "") + build(i - 1 , g || (j > l) , f);
            if (j || mx) f[j]--;
        }
    }

public:
    ll findNext(string t) {
        s = t;
        reverse(s.begin() , s.end());
        s = s + string(N - s.size() - 1, '0');
        return stoll(build(N - 2 , 0 , vi(10 , 0)));
    }
};
