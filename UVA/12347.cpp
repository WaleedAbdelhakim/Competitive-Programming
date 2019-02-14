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

const int N = 1e6 + 6;
int L[N] , R[N];

void post_order(int node) {
    if(L[node] != -1)
        post_order(L[node]);
    if(R[node] != -1)
        post_order(R[node]);
    printf("%d\n" , node);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif

    memset(L , -1 , sizeof L);
    memset(R , -1 , sizeof R);

    vi info;
    int n , root;
    while(scanf("%d" , &n) == 1) {
        if(info.empty()) {
            info.pb(n);
            root = n;
            continue;
        }

        if(n < info.back()) {
            L[info.back()] = n;
            info.pb(n);
        } else {
            int p;
            while(info.size() && n > info.back())  {
                p = info.back();
                info.pop_back();
            }
            R[p] = n;
            info.pb(n);
        }
    }

    post_order(root);

}