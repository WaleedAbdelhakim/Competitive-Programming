#include <bits/stdc++.h>

//#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

//template<typename T>
//using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef vector<int> vi;
typedef long long ll;

#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
#define watch(x) cout << (#x) << " is " << (x) << endl

int di[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dj[] = {1, -1, 0, 0, -1, 1, 1, -1};

const int N = 12 , M = 1e3 + 5;
vi cost[N][N];
int n , k;
int memo[N][M];

int solve(int node , int day) {
    if(day == k)
        return node == n ? 0 : inf;

    int &ret = memo[node][day];
    if(~ret)
        return ret;

    ret = inf;
    for (int i = 1 ;i <= n ;i++) {
        if(i == node || !cost[node][i][day % cost[node][i].size()]) continue;
        ret = min(ret , solve(i , day + 1) + cost[node][i][day % cost[node][i].size()]);
    }

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int test = 1;
    while(scanf("%d%d",&n,&k) , (n || k)) {
        for (int i = 0 ;i < N ;i++)
            for (int j = 0 ;j < N ;j++)
                cost[i][j].clear();

        int cnt , co;
        for (int i = 1 ;i <= n ;i++) {
            for (int j = 1 ;j <= n ;j++) {
                if(i == j) continue;
                scanf("%d",&cnt);
                while(cnt--) {
                    scanf("%d",&co);
                    cost[i][j].pb(co);
                }
            }
        }

        memset(memo , -1 , sizeof memo);
        printf("Scenario #%d\n" , test++);

        int ans = solve(1 , 0);
        if(ans == inf)
            puts("No flight possible.\n");
        else
            printf("The best flight costs %d.\n\n" , ans);
    }
}