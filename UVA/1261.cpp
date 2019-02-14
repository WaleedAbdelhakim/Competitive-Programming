#include <bits/stdc++.h>
#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
using namespace std;

typedef vector<int> vi;
typedef long long ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 , -1 , 0 , 0 , -1 , 1 ,  1 , -1};


map<string , bool> memo;
bool solve(string msk) {
    if(!msk.size())
        return 1;

    if(memo.count(msk))
        return memo[msk];

    for (int i = 0 ;i < msk.size() ;i++) {
        string t = msk;
        if(msk[i] == '1') {
            if(i == 0 || i == msk.size()-1)
                t.erase(i , 1);
            else {
                t.erase(i+1 , 1);
                t.erase(i-1 , 1);
            }

            if(solve(t))
                return memo[msk] = 1;
        }
    }

    return memo[msk] = 0;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    scanf("%d" , &T);

    string s;
    while(T--) {
        cin >> s;
        int prevCnt = 1;
        char prev = s[0];

        string msk = "";
        for (int i = 1 ;i < s.size() ;i++) {
            if(s[i] == prev)
                prevCnt++;
            else {
                msk += prevCnt > 1 ? "1" : "0";
                prev = s[i];
                prevCnt = 1;
            }
        }

        msk += prevCnt > 1 ? "1" : "0";

        printf("%d\n",solve(msk));
    }
}