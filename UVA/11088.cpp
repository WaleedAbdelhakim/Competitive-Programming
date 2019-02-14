#include <bits/stdc++.h>
#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
using namespace std;

typedef vector<int> vi;
typedef long long ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1, -1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 15;
int n;
int arr[N] , memo[1 << N];

vi adj[N + 5];

void pre() {
    for (int i = 3 ;i <= 15 ;i++) {
        for (int j = 0 ;j < (1 << i) ;j++) {
            if(ones(j) != 3) continue;
            adj[i].pb(j);
        }
    }
}

vi getAvailMasks(int mask) {
    vi availPos , masks;
    for (int i = 0 ;i < n ;i++)
        if(!(mask & (1 << i)))
            availPos.pb(i);

    int sz = availPos.size();
    for (int m : adj[sz]) {
        int nwMask = 0 , sum = 0;
        for (int i = 0 ;i < availPos.size() ;i++) {
            if(m & (1 << i)) {
                nwMask |= (1 << availPos[i]);
                sum += arr[availPos[i]];
            }
        }
        if(sum >= 20)
            masks.pb(nwMask);
    }

    return masks;
}

int solve(int mask) {
    if(n - ones(mask) < 3)
        return 0;

    int &ret = memo[mask];
    if(~ret)
        return ret;

    vi availMasks = getAvailMasks(mask);
    ret = 0;
    for (int m : availMasks)
        ret = max(ret , solve(mask | m) + 1);

    return ret;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif

    pre();
    int test = 1;
    while(scanf("%d",&n) , n) {
        for (int i = 0 ;i < n ;i++)
            scanf("%d" , arr + i);

        memset(memo , -1 , sizeof memo);
        printf("Case %d: %d\n" , test++ , solve(0));
    }
}