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

const int N = 1000;
int n, m;
bool grid[N][N];
int ways[N][N];

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);

    for (int test = 0; test < T; test++) {
        scanf("%d%d", &n, &m);
        cin.ignore();

        memset(ways, 0, sizeof ways);
        memset(grid, 0, sizeof grid);

        int r, c;
        for (int i = 0; i < n; i++) {
            string s;
            getline(cin, s);
            stringstream t(s);
            t >> r;
            while (t >> c) {
                grid[r - 1][c - 1] = 1;
            }

        }

        ways[0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i != n - 1 && !grid[i + 1][j])
                    ways[i + 1][j] += ways[i][j];
                if (j != m - 1 && !grid[i][j + 1])
                    ways[i][j + 1] += ways[i][j];
            }
        }

        if(test)
            puts("");

        printf("%d\n", ways[n - 1][m - 1]);
    }
}