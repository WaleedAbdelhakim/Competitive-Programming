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

const int N = 1e6 + 6 , M = 25;
int h , k;
int arr[N] , sz[N] , n;
bool leaf[N];

int pre_order(int &ind, int height) {
    if(height > h)
        return 0;
    int node = ind;
    sz[node] = 1;
    ind++;
    sz[node] += pre_order(ind , height + 1);
    sz[node] += pre_order(ind , height + 1);
    leaf[node] = sz[node] == 1;
    return sz[node];
}

int vis[N][M] , vid;
int memo[N][M];
int solve(int ind , int rem) {
    if(ind == n)
        return 0;

    int &ret = memo[ind][rem];
    if(vis[ind][rem] == vid)
        return ret;

    vis[ind][rem] = vid;
    ret = -inf;

    if(rem)
        ret = solve(ind + sz[ind] , rem - 1) + arr[ind];

    if(!leaf[ind])
        ret = max(ret , solve(ind + 1 , rem));

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    while(scanf("%d%d" , &h,&k) , ~h) {
        n = (1 << (h + 1)) - 1;

        for (int i = 0 ;i < n ;i++)
            scanf("%d" , arr + i);

        int i = 0;
        pre_order(i , 0);
        ++vid;
        printf("%d\n" , solve(0 , k));
    }
}