#include <bits/stdc++.h>

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

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

struct info {
    int r, c;
    char next;
};

const int N = 11 , MOD =  20437;
int n;
char grid[N][N], dest;
int ways[N][N][100];
int dist[N][N][100];

bool valid(int r, int c, char next) {
    return r >= 0 && r < n && c >= 0 && c < n && (grid[r][c] == '.' || (grid[r][c] >= 'A' && grid[r][c] <= next) );
}

pair<int, int> solve(int r, int c) {
    memset(ways, 0, sizeof ways);
    memset(dist , 0 , sizeof dist);
    queue<info> turn;

    turn.push({r, c, 'A'});
    ways[r][c]['A'] = 1;
    dist[r][c]['A'] = 0;

    int dep = 0;
    while (turn.size()) {
        int sz = turn.size();
        while (sz--) {
            info cur = turn.front();
            turn.pop();
            int r = cur.r, c = cur.c;
            char next = cur.next;

            if (grid[r][c] == dest)
                return {dep, ways[r][c][next]};

            for (int k = 0; k < 4; k++) {
                int nwr = r + di[k], nwc = c + dj[k];
                char nwNext = next + (grid[r][c] == next);
                if (valid(nwr, nwc, nwNext)) {
                    if (ways[nwr][nwc][nwNext] != 0 && dist[nwr][nwc][nwNext] == dep + 1)
                        ways[nwr][nwc][nwNext] = (ways[nwr][nwc][nwNext] + ways[r][c][next]) % MOD;
                    else if(!ways[nwr][nwc][nwNext]){
                        turn.push({nwr, nwc, nwNext});
                        dist[nwr][nwc][nwNext] = dep + 1;
                        ways[nwr][nwc][nwNext] = ways[r][c][next];
                    }
                }
            }
        }
        dep++;
    }

    return {0 , 0};
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int test = 1;
    while (scanf("%d", &n), n) {
        int r, c;

        dest = 'A';
        for (int i = 0; i < n; i++) {
            scanf("%s", &grid[i]);
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != '.' && grid[i][j] != '#') {
                    if (grid[i][j] == 'A')
                        r = i, c = j;
                    dest = max(dest, grid[i][j]);
                }
            }
        }

        auto ans = solve(r, c);
        if (!ans.second)
            printf("Case %d: Impossible\n", test++);
        else
            printf("Case %d: %d %d\n", test++, ans.first, ans.second);
    }
}