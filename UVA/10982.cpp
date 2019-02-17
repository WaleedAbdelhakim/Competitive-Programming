#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;

#define pb push_back

const int N = 105;
int n , m;
bool color[N];

vi adj[N];

void init () {
    for (int i = 1 ;i < N ;i++)
        adj[i].clear() , color[i] = 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int T;
    scanf("%d" , &T);
    for (int c = 1 ; c <= T ; c++) {
        init();
        scanf("%d%d" , &n , &m);

        int u , v;
        for (int i = 0 ;i < m ;i++) {
            scanf("%d%d" , &u , &v);
            adj[u].pb(v);
            adj[v].pb(u);
        }

        int pairs = m , cnt = 0;
        while (1) {
            bool ch = 0;
            for (int i = 1 ;i <= n ;i++) {
                int d = 0;
                for (int v : adj[i]) {
                    d -= color[i] == color[v];
                    d += color[i] != color[v];
                }

                if (d < 0) {
                    ch = 1;
                    pairs += d;
                    color[i] = !color[i];
                    cnt += color[i];
                    cnt -= !color[i];
                }
            }

            if (!ch) break;
        }

        printf("Case #%d: " , c);
        if (pairs * 2 <= m) {
            printf("%d\n" , cnt);
            for (int i = 1 ;i <= n ;i++)
                if (color[i])
                    printf("%d " , i);
            puts("");
        } else {
            puts("Impossible.");
        }
    }
}