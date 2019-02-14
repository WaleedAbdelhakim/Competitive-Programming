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

const int N = 21;
int n;
int arr[N] , memo[4][1 << N];

int sum;

int getSum(int msk) {
    int ret = 0;
    for (int i = 0 ;i < n ;i++)
        if(msk & (1 << i))
            ret += arr[i];
    return ret;
}

bool solve(int ind ,int msk , int sumSoFar) {
    if(sumSoFar > (ind + 1) * sum)  
        return 0;
    if(ind == 3)
        return 1;

    int &ret = memo[ind][msk];
    if(~ret)
        return ret;


    if(sumSoFar == (ind + 1) * sum)
        return solve(ind + 1 , msk , sumSoFar);

    for (int i = 0 ;i < n ;i++) {
        if(msk & (1 << i)) continue;
        if(solve(ind , msk | (1 << i) , sumSoFar + arr[i]))
            return ret = 1;
    }

    return ret = 0;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    scanf("%d",&T);

    while(T--) {
        scanf("%d",&n);
        sum = 0;
        for (int i = 0 ;i < n ;i++)
            scanf("%d" , arr + i) , sum += arr[i];

        if(sum % 4 != 0) {
            puts("no");
            continue;
        }

        sum /= 4;

        memset(memo , -1 , sizeof memo);
        if(solve(0 , 0 , 0))
            puts("yes");
        else
            puts("no");
    }
}