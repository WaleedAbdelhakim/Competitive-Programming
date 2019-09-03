#include <bits/stdc++.h>

using namespace std;

const int B1 = 256;
const int B2 = 128;
const int MOD1 = 2000000011;
const int MOD2 = 1000000007;

const int N = 1e5 + 5;
int m , Log;
char s[N];
pair<int, int> prefix[N];
vector<pair<int , char> > adj[N];

int mul(int a , int b , int m) {
    return a * 1ll * b % m;
}

int add(long long a , int b , int m) {
    a += b;
    while (a >= m)a -= m;
    while (a < 0) a += m;
    return a;
}

void hash_prefix() {
    int h1, h2;
    h1 = h2 = 0;
    for (int i = 0; s[i]; i++) {
        h1 = ((1LL * h1 * B1) % MOD1 + s[i]) % MOD1;
        h2 = ((1LL * h2 * B2) % MOD2 + s[i]) % MOD2;
        prefix[i] = make_pair(h1, h2);
    }
}

int p[N] , pp[N];
void pre() {
    p[0] = pp[0] = 1;
    for (int i = 1 ;i < N ;i++) {
        p[i] = mul(p[i - 1] , B1 , MOD1);
        pp[i] = mul(pp[i - 1] , B2 , MOD2);
    }
}

map<pair<int , int> , int> hash_to_node;
void dfs(int node , int h1 ,int h2) {
    hash_to_node[{h1 , h2}] = node;
    for (auto c : adj[node])
        dfs(c.first , add(mul(h1 , B1 , MOD1) , c.second , MOD1)
                , add(mul(h2 , B2 , MOD2) , c.second , MOD2));
}

pair<int , int> get(int l , int r) {
    if (!l) return prefix[r];
    int len = r - l + 1;
    return {add(prefix[r].first , -mul(p[len] , prefix[l - 1].first , MOD1) , MOD1)
            , add(prefix[r].second, -mul(pp[len] , prefix[l - 1].second , MOD2) , MOD2)};
}

int par[N][18];
void build() {
    for (int j = 0 ;j < Log ;j++)
        for (int i = 0 ;i <= m + 1 ;i++)
            par[i][j] = -1;

    for (int i = 0 ;i < m ;i++) {
        int l = i , r = m - 1 , theOne = i + 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (hash_to_node.count(get(i , mid)))
                theOne = mid + 2, l = mid + 1;
            else
                r = mid - 1;
        }

        if (theOne <= m + 1)
            par[i][0] = theOne;
    }
    for (int j = 1 ;j < Log ;j++)
        for (int i = 0 ;i < m ;i++)
            if (~par[i][j - 1])
                par[i][j] = par[par[i][j - 1]][j - 1];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T, n, q;
    scanf("%d", &T);
    pre();

    while (T--) {
        scanf("%d%d%d", &n, &m, &q);

        for (int i = 0 ;i <= n ;i++) adj[i].clear();
        hash_to_node.clear();
        Log = log2(m) + 1;

        int p;
        char c;
        for (int i = 1; i <= n; i++) {
            scanf("%d %c", &p, &c);
            adj[p].push_back({i, c});
        }

        scanf("%s", s);
        dfs(0 , 0 , 0);
        hash_prefix();
        build();

        int l , r;
        while (q--) {
            scanf("%d%d" , &l , &r);
            l-- , r--;
            int fails = 0;
            for (int j = Log - 1 ;j >= 0 ;j--) {
                if (~par[l][j] && par[l][j] <= r + 1) {
                    fails += 1 << j;
                    l = par[l][j];
                }
            }
            printf("%d %d\n" , fails , hash_to_node[get(l , r)]);
        }
    }
}