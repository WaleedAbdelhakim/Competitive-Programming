#include <bits/stdc++.h>

using  namespace std;


const int N = 505 , M = N * N + N;
int n , m;
int husband[M] , vis[M + M] , vid;
vector<int> adj[M + M];
char arr[N][N];

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
    for (int i = 0 ;i < n ;i++) {
        for (int j = 0 ;j < m ;j++) {
            if (arr[i][j] == 'B') {
                vid++;
                cnt += find_match(i * m + j + M);
                vid++;
                cnt += find_match(i * m + j);
            }
        }
    }
    return cnt;
}

void add_edge(int r , int c , int r1 , int c1 , int add = 0) {
    int u = r * m + c + add;
    int v = r1 * m + c1;
    adj[u].push_back(v);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int T;
    scanf("%d" , &T);
    while (T--) {
        for (int i = 0 ;i < M + M ;i++)
            adj[i].clear();

        scanf("%d%d" , &n , &m);
        for (int i = 0 ;i < n ;i++)
            scanf("%s" , &arr[i]);

        int b = 0 , w = 0;
        for (int i = 0 ;i < n ;i++) {
            for (int j = 0 ;j < m ;j++) {
                if (arr[i][j] == 'B') {
                    b++;
                    if (i + 1 < n && arr[i + 1][j] == 'W')
                        add_edge(i, j, i + 1, j);
                    if (i - 1 >= 0 && arr[i - 1][j] == 'W')
                        add_edge(i, j, i - 1, j);
                    if (j + 1 < m && arr[i][j + 1] == 'W')
                        add_edge(i, j, i, j + 1, M);
                    if (j - 1 >= 0 && arr[i][j - 1] == 'W')
                        add_edge(i, j, i, j - 1, M);

                }

                w += arr[i][j] == 'W';
            }
        }

        if (w != 2 * b || max_match() != 2 * b)
            puts("NO");
        else
            puts("YES");

    }
}