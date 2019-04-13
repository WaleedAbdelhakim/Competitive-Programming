// i got the solution from :
// https://github.com/MohamedNabil97/CompetitiveProgramming/blob/master/TopCoder/SRM447-D1-500.cpp

#include <bits/stdc++.h>

using namespace std;

const int N = 45; // max man node
const int M = 45; // max woman node
vector<int> adj[N] , men;
int husband[M] , vis[N] , vid;
bool find_match(int node) {
    if (vis[node] == vid)
        return 0;

    vis[node] = vid;
    for (int child : adj[node]) {
        if (husband[child] == -1 || find_match(husband[child])) {
            husband[child] = node;
            return 1;
        }
    }

    return 0;
}

int max_match(int n) {
    memset(husband , -1 , sizeof husband);
    int cnt = 0;
    for (int i = 0 ;i < n ;i++) { // loop over men
        ++vid;
        cnt += find_match(i);
    }
    return cnt;
}

class PeopleYouMayKnow {
public:
    int maximalScore(vector <string> f, int person1, int person2) {
        vector<bool> deleted(f.size() , 0);
        int ret = 0;
        for (int i = 0 ;i < f.size() ;i++) {
            deleted[i] = f[person1][i] == 'Y' && f[i][person2] == 'Y';
            ret += deleted[i];
        }

        for (int i = 0 ;i < f.size() ;i++)
            for (int j = 0 ;j < f.size() ;j++)
                if (f[i][j] == 'Y' && f[person1][i] == 'Y' && f[j][person2] == 'Y' && !(deleted[i]+deleted[j]))
                    adj[i].push_back(j);

        return ret + max_match(f.size());
    }
};
