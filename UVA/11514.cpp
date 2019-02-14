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

struct superPower {
    int attack , calories;
};

const int N = 1005;
int n , m , e;
superPower power[N];
int villain[N] , memo[N][N];
bool effect[N][N];

int solve(int i , int j) {
    if(j == m)
        return 0;
    if(i == n)
        return inf;

    int &ret = memo[i][j];
    if(~ret)
        return ret;

    ret = solve(i + 1 , j);
    if(effect[i][j] && power[i].attack >= villain[j])
        ret = min(ret , solve(i + 1 , j + 1) + power[i].calories);

    return ret;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    while(scanf("%d%d%d",&n,&m,&e) , n && m && e) {
        map<string , int> ind;
        string name;
        for (int i = 0 ;i < n ;i++) {
            cin >> name >> power[i].attack >> power[i].calories;
            ind[name] = i;
        }

        memset(effect , 0 , sizeof effect);
        string weapons;
        for (int i = 0 ;i < m ;i++) {
            cin >> name >> villain[i] >> weapons;
            string cur = "";
            for (int j = 0 ;j < weapons.size() ;j++) {
                if(weapons[j] == ',') {
                    effect[ind[cur]][i] = 1;
                    cur = "";
                } else
                    cur += weapons[j];
            }
            effect[ind[cur]][i] = 1;
        }

        memset(memo , -1 , sizeof memo);
        if(solve(0 , 0) <= e)
            puts("Yes");
        else
            puts("No");
    }
}