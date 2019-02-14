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

const int N = 27;
int n;
char a[N] , b[N] ;
int R[91] , L[91] , pos[91];
bool done[91];

void post_order(int node) {
    if(L[node] != -1)
        post_order(L[node]);
    if(R[node] != -1)
        post_order(R[node]);
    printf("%c",node);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    while(scanf("%s%s" , a , b) == 2) {
        n = strlen(a);
        for (int i = 0 ;i < n ;i++)
            pos[b[i]] = i;

        memset(R , -1 , sizeof R);
        memset(L , -1 , sizeof L);
        memset(done , 0 , sizeof done);

        for (int i = 0 ;i < n ;i++)  {
            int theOne = -1;
            for (int j = i + 1 ;j < n ;j++) {
                if(pos[a[j]] > pos[a[i]]) {
                    theOne = a[j];
                    break;
                }
            }

            if(theOne != -1 && !done[theOne])
                R[a[i]] = theOne , done[theOne] = 1;
        }

        for (int i = 0 ;i < n - 1 ;i++)
            if(!done[a[i + 1]])
                L[a[i]] = a[i + 1];

        post_order(a[0]);
        puts("");
    }
}