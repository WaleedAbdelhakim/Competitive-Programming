#include <bits/stdc++.h>
#include <math.h>
#define pb push_back
#define INF 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long   ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 305;
int s , e;

vi info;
ll memo[N][N][N];

ll solve(int pay ,int coins , int k){
    if(k == 0)
        return  pay == 0 && coins == 0;

    ll &ret = memo[pay][coins][k];
    if(~ret)
        return ret;

    ret = solve(pay , coins , k-1);
    if(pay >= k && coins >= 1)
        ret += solve(pay-k , coins-1 , k);

    return ret;
}
int main(){
    string line;
    memset(memo , -1 , sizeof memo);
    while(getline(cin , line)){
        istringstream t(line);

        info = vi(3 , -1);
        int x , i = 0;
        while(t >> info[i++]);

        ll ans = 0;

        int s = info[2] == -1 ? 1 : info[1];
        int e = info[2] == -1 ? (info[1] == -1 ? info[0] : info[1]) : info[2];

        e = min(e , N);
        s = max(1 , s);

        for(int i = s ;i <= e ;i++)
            ans += solve(info[0] , i , N);

        printf("%lld\n" , info[0] == 0 && (info[2] == -1 || info[1] == 0) ? 1 : ans);
    }

}
