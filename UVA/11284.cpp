#include <bits/stdc++.h>

using namespace std;

const int N = 55 , M = 13;
int n , m , p;
int arr[M] , vis[M][1 << M] , vid;
double save[N] , memo[M][1 << M] , dist[N][N] , eps = 1e-6;

void floyd() {
    for(int k = 0; k <= n; k++)
        for(int i = 0; i <= n; i++)
            for(int j = 0; j <= n; j++)
                dist[i][j] = min(dist[i][k] + dist[k][j] , dist[i][j]);
}

double solve (int i , int mask) {
    double &ret = memo[i][mask];
    if (vis[i][mask] == vid)
        return ret;

    vis[i][mask] = vid;
    ret = -dist[arr[i]][0];
    for (int j = 0 ;j < p ;j++) {
        if (!(mask & (1 << j))) {
            ret = max(ret , solve(j , mask | (1 << j)) + save[arr[j]] - dist[arr[i]][arr[j]]);
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(0) ; cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    cin >> T;

    while (T--) {
        cin >> n >> m;
        for (int i = 0 ;i <= n ;i++) {
            for (int j = 0 ;j <= n ;j++)
                dist[i][j] = 1e9;

            save[i] = 0;
        }

        int u , v;
        double c;
        while (m--) {
            cin >> u >> v >> c;
            dist[v][u] = dist[u][v] = min(dist[u][v] , c);
        }

        floyd();
        cin >> p;
        for (int i = 0 ;i < p ;i++) {
            cin >> arr[i] >> c;
            save[arr[i]] += c;
        }

        sort(arr , arr + p);
        p = unique(arr , arr + p) - arr;
        arr[p] = 0;

        vid++;

        double ans = solve(p , 0);
        if (ans <= 0 || abs(ans) < eps)
            cout << "Don't leave the house\n";
        else
            cout << "Daniel can save $" << fixed << setprecision(2) << ans << '\n';
    }
}