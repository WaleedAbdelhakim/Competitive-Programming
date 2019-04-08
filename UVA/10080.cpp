#include <bits/stdc++.h>

using namespace std;


const int N = 105; // max man node
const int M = 105; // max woman node
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

int max_match(int n) {
    memset(husband , -1 , sizeof husband);
    int cnt = 0;
    for (int i = 0 ;i < n ;i++) { // loop over men
        ++vid;
        cnt += find_match(i);
    }
    return cnt;
}

void init() { // every test case
    for (int i = 0 ;i < N ;i++)
        adj[i].clear();
}


long double x[N] , y[N] , xx[N] , yy[N];

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int n , m , s , v;
    while (cin >> n >> m >> s >> v) {
        init();

        for (int i = 0 ;i < n ;i++)
            cin >> x[i] >> y[i];

        for (int i = 0 ;i < m ;i++)
            cin >> xx[i] >> yy[i];

        int sv2 = s * s * v * v;
        for (int i = 0 ;i < n ;i++) {
            for (int j = 0 ;j < m ;j++) {
                long double dy2 = (yy[j] - y[i]) * (yy[j] - y[i]);
                long double dx2 = (xx[j] - x[i]) * (xx[j] - x[i]);
                if (dy2 + dx2 <= sv2)
                    adj[i].push_back(j);
            }
        }

        cout << n - max_match(n) << '\n';
    }
}