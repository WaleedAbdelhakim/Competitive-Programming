#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const double eps = 1e-7;
ll memo[9][105][2];
vector<int> sec;

class Lottery {
    ll solve (int i , int last , int equal) {
        if (i == 0)
            return 1;

        ll &ret = memo[i][last][equal];
        if (~ret)
            return ret;

        ret = 0;
        for (int j = equal ? last : last - 1 ; j >= 1 ;--j)
            ret += solve(i - 1 , j , equal);

        return ret;
    }
public:
    vector<string> sortByOdds(vector<string> rules) {
        vector<pair<ll, string> > info;
        memset(memo , -1 , sizeof memo);
        for (int i = 0 ;i < rules.size() ;i++) {
            pair<ll , string> cur;
            cur.second = rules[i].substr(0 , rules[i].find(':'));
            int choices , blanks;
            char sor , uni;
            stringstream t(rules[i].substr(rules[i].find(':') + 1));
            t >> choices >> blanks >> sor >> uni;

            cur.first = 1;
            if (sor == 'F' && uni == 'F')
                for (int j = 0 ;j < blanks ;j++) cur.first *= choices;
            else if (sor == 'F' && uni == 'T')
                for (int j = choices ; j > choices - blanks ;j--) cur.first *= j;
            else if (sor == 'T' && uni == 'F')
                cur.first= solve(blanks , choices , 1);
            else
                cur.first = solve(blanks , choices + 1 , 0);

            info.push_back(cur);
        }

        sort(info.begin() , info.end());
        vector<string> ret;
        for (auto &c : info) ret.push_back(c.second);
        return ret;
    }

};
