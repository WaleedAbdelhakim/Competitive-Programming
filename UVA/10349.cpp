#include <bits/stdc++.h>

using namespace std;


const int X = 40;
const int N = X * X; // max man node
const int M = X * X; // max woman node
vector<int> adj[N];
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

int max_match() {
    memset(husband , -1 , sizeof husband);
    int cnt = 0;
    for (int i = 0 ;i < N ;i++) { // loop over men
        ++vid;
        cnt += find_match(i);
    }
    return cnt;
}

void init() { // every test case
    for (int i = 0 ;i < N ;i++)
        adj[i].clear();
}

int di[] = {0, 0, 1, -1};
int dj[] = {1, -1, 0, 0};

int n , m;
char grid[X][X];

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    scanf("%d" , &T);
    while (T--) {
        init();
        scanf("%d%d" , &n, &m);
        for (int i = 0 ;i < n ;i++)
            scanf("%s" , &grid[i]);

        int men = 0 , women = 0;
        for (int i = 0 ;i < n ;i++) {
            int color = i % 2;
            for (int j = 0 ;j < m ;j++) {
                if (color && grid[i][j] == '*') {
                    for (int k = 0 ;k < 4 ;k++) {
                        int nwi = i + di[k] , nwj = j + dj[k];
                        if (nwi >= 0 && nwi < n && nwj >= 0 && nwj < m && grid[nwi][nwj] == '*') {
                            int u = i * m + j , v = nwi * m + nwj;
                            adj[u].push_back(v);
                        }
                    }
                    men++;
                } else if (grid[i][j] == '*')
                    women++;

                color = !color;
            }
        }

        printf("%d\n" , men + women - max_match());
    }
}
