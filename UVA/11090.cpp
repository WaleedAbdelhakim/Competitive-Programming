// for every possible start of the cycle s [1 , n] we will choose the length of the cycle k [1 , n]
// and using dp we will find the minmum cycle length starting from node s with length exactly k 
// and minimize the answer with the mean of the bestCycle : (bestCycleLen / k) 
// dp complexity for each start O(n^2)
// total complexity O(n^3)


#include <bits/stdc++.h>

using namespace std;

const int N = 55;
int memo[N][N];

vector<pair<int , int> > adj[N];
int start , len;
int solve(int node , int dep) {
    if ((node == start && dep != len) || !dep)
        return node == start && !dep ? 0 : 1e9;

    int &ret = memo[node][dep];
    if (~ret)
        return ret;

    ret = 1e9;
    for (auto c : adj[node])
        ret = min(ret , solve(c.first , dep - 1) + c.second);

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int t , n , m;
    scanf("%d" , &t);
    for (int test = 1 ; test <= t ; test++) {
        scanf("%d%d" , &n , &m);
        int u , v , c;

        fill(adj , adj + N , vector<pair<int , int> > ());

        while (m--) {
            scanf("%d%d%d" , &u , &v , &c);
            adj[u].push_back({v , c});
        }

        double ans = 1e9;
        for (start = 1 ; start <= n ; start++) {
            memset(memo , -1 , sizeof memo);
            for (len = 1 ; len <= n ; len++) {
                double cur = solve(start , len);
                if (cur != 1e9)
                    ans = min(ans , cur / len);
            }
        }

        if (ans == 1e9)
            printf("Case #%d: No cycle found.\n" , test);
        else
            printf("Case #%d: %.2f\n" , test , ans);
    }
}
