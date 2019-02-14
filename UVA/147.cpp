#include <bits/stdc++.h>
#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef  unsigned long long   ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 5e4 + 5 , M = 11;
int arr[] = {10000 , 5000 , 2000 , 1000 , 500 , 200 , 100 , 50 , 20 , 10 , 5};

ll memo[M + 5][N];
bool vis[M + 5][N] = {0};
double eps = 1e-7;
ll solve(int i ,int rem){
    if(i == M)
        return rem == 0;

    ll &ret = memo[i][rem];
    if(vis[i][rem])
        return ret;
    vis[i][rem] = 1;

    ret = solve(i+1 , rem);
    if(rem >= arr[i])
        ret += solve(i , rem - arr[i]);

    return ret;
}
int main() {
    double num;
    memset(vis , 0 , sizeof vis);
    while(cin >> num , num != 0.0){
        cout << fixed << setw(6) << setprecision(2) << num;
        cout << setw(17) << solve(0 ,num * 100 + eps) << endl;
    }
}
