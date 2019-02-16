#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 1e9
#define all(v) (v).begin() , (v).end()
#define mask bitset<16>


using namespace std;

typedef vector<int> vi;
typedef long long ll;

const int N = 16 , M = (1 << 17);

int n;
int arr[N][N];
int memo[N][M];


vi info;
void p(int i ,mask m ,mask done){
    if(i >= n){
        info.pb(done.to_ulong());
        return;
    }
    p(i+1 , m , done);
    if(m[i] == 1){
        done[i] = 1;
        p(i+2 , m , done);
    }
}
mask next(mask m){
    mask nw;
    nw.set();
    for(int i = 0 ;i < n ;i++){
        if(m[i] == 1){
            if(i != 0)
                nw[i-1] = 0;
            if(i != n-1)
                nw[i+1] = 0;
            nw[i] = 0;
        }
    }
    return nw;
}
int solve(int ind , mask m){
    if(ind == n)
        return 0;

    int &ret = memo[ind][m.to_ulong()];
    if(ret != -1)
        return ret;

    info.clear();
    p(0 , m ,mask());
    vi nw = info;
    ret = 0;
    for(int x : nw){
        mask cur(x);
        int sum = 0;
        for(int j = 0 ;j < n ;j++)
            sum += (cur[j] == 1 ? arr[ind][j] : 0);
        ret = max(ret ,sum + solve(ind+1 , next(cur)));
    }
    return ret;
}
int main(){
    string s;
    while(getline(cin , s) && s != ""){
        stringstream t;
        t << s;
        vi info;
        n = 0;
        while(t >> arr[0][n]) n++;
        for(int i = 1 ;i < n ;i++){
            getline(cin , s);
            t.clear();
            t << s;
            int c = 0;
            while(t >> arr[i][c])c++;
        }

        mask m;
        m.set();

        memset(memo , -1 , sizeof memo);

        printf("%d\n",solve(0 , m));

        getline(cin , s);
    }
}
