#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

//template <typename T>
//using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef vector<int> vi;
typedef long long ll;

#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
#define watch(x) cout << (#x) << " is " << (x) << endl

/*int di[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dj[] = {1, -1, 0, 0, -1, 1, 1, -1};*/

int di[3][4] = {{0, 0, 1, -1},
                {0, 0, 2, -2},
                {0, 0, 3, -3}};

int dj[3][4] = {{1, -1, 0, 0},
                {2, -2, 0, 0},
                {3, -3, 0, 0}};

const int N = 305;
int n, m;
char grid[N][N];
bool vis[N][N][3];

struct state {
    int r, c, move;
};

bool valid(int r,  int c) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

bool clear(int r , int c , int r2 , int c2) {
    for (int i = min(r , r2) ;i <= max(r , r2);i++)
        for (int j = min(c , c2) ;j <= max(c , c2) ;j++)
            if(grid[i][j] == '#')
                return 0;
    return 1;
}

int bfs(int r, int c) {
    memset(vis, 0, sizeof vis);
    queue<state> turn;
    turn.push({r, c, 0});
    vis[r][c][0] = 1;

    int dep = 0;
    while (turn.size()) {
        int sz = turn.size();
        while (sz--) {
            state cur = turn.front();
            turn.pop();

            if (grid[cur.r][cur.c] == 'E')
                return dep;

            for (int k = 0 ;k < 4 ;k++) {
                int nwr = cur.r + di[cur.move][k];
                int nwc = cur.c + dj[cur.move][k];
                int m = (cur.move + 1) % 3;
                if(valid(nwr , nwc) && clear(cur.r , cur.c , nwr , nwc) && !vis[nwr][nwc][m]) {
                    vis[nwr][nwc][m] = 1;
                    turn.push({nwr , nwc , m});
                }
            }
        }

        dep++;
    }

    return -1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &n, &m);

        int r, c;
        for (int i = 0; i < n; i++) {
            scanf("%s", &grid[i]);
            for (int j = 0; j < m; j++)
                if (grid[i][j] == 'S')
                    r = i, c = j;
        }

        int ans = bfs(r , c);
        if(ans == -1)
            puts("NO");
        else
            printf("%d\n" , ans);
    }
}