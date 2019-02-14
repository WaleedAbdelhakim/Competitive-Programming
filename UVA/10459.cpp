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

const int N = 5e3 + 5;
int n;
vi adj[N];
int Deg[N];

int getDimeter(vi & centers) { // at most two centers
    queue<int> leafs;
    for (int i = 1 ;i <= n ;i++)
        if(Deg[i] == 1)
            leafs.push(i);

    int d = 0;
    int cnt = n;
    while(cnt > 2) {
        d += 2;
        int sz = leafs.size();
        cnt -= sz;
        while(sz--) {
            int cur = leafs.front();
            leafs.pop();
            for (int par : adj[cur]) {
                Deg[par]--;
                if(Deg[par] == 1)
                    leafs.push(par);
            }
        }
    }


    while(leafs.size())
        centers.pb(leafs.front()) , leafs.pop();

    return d + (centers.size() == 2);
}

vi worset;
int atLeast;
void dfs(int node , int par , int dep) {
    bool leaf = 1;
    for (int child : adj[node])
        if(child != par)
            dfs(child , node , dep + 1) , leaf = 0;
    if(leaf && dep == atLeast)
        worset.pb(node);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    while(scanf("%d",&n) == 1) {
        for (int i = 1 ;i <= n ;i++)
            adj[i].clear();

        for (int i = 1 ;i <= n ;i++) {
            scanf("%d", Deg + i);
            int v;
            for (int j = 0 ;j < Deg[i] ;j++) {
                scanf("%d",&v);
                adj[i].pb(v);
            }
        }

        vi centers;
        int dimeter = getDimeter(centers);
        atLeast = ceil(dimeter / 2.0);

        worset.clear();

        dfs(centers[0] , -1 , 0);
        if(dimeter&1)
            dfs(centers[1] , -1 , 0);

        sort(all(centers));
        printf("Best Roots  : ");
        for (int i = 0 ;i < centers.size() ;i++)
            printf("%d%c" , centers[i] , " \n"[i == centers.size() - 1]);

        sort(all(worset));
        printf("Worst Roots : ");
        for (int i = 0 ;i < worset.size() ;i++)
            printf("%d%c" , worset[i] , " \n"[i == worset.size() - 1]);
    }
}