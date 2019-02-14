#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

vi p;
int n , k;
ll memo[200][16][1150];
bool isprime(int n){
    for(int i = 2 ;i * i <= n ;i++)
        if(n % i == 0)
            return 0;
    return 1;
}
ll solve(int i ,int j ,int rem){
    if(i == p.size() || j == k)
        return j == k && rem == 0;

    ll &ret = memo[i][j][rem];
    if(ret != -1)
        return ret;
        
    ret = 0;
    if(p[i] <= rem)
        ret += solve(i+1 , j+1 , rem-p[i]);
    ret += solve(i+1 , j , rem);

    return ret;
}
int main(){
    for(int i = 2 ;i <= 1120 ;i++)
        if(isprime(i))
            p.pb(i);

    while(scanf("%d%d",&n,&k) , (n || k)){
        memset(memo , -1 , sizeof memo);
        printf("%lld\n" , solve(0 , 0 , n));
    }
}
