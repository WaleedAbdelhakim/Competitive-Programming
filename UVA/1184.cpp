#include <bits/stdc++.h>

using namespace std;


const int N = 122; // max man node
const int M = 122; // max woman node
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

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int T , n , m;
    scanf("%d" , &T);
    while (T--) {
        init();
        scanf("%d%d" , &n , &m);
        int u , v;
        while (m--) {
            scanf("%d%d" , &u , &v);
            adj[u].push_back(v);
        }

        printf("%d\n" , n - max_match(n));
    }
}