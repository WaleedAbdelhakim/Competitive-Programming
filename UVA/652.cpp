#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

//template<typename T>
//using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef vector<int> vi;
typedef long long ll;

#define S second
#define F first
#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
#define watch(x) cout << (#x) << " is " << (x) << endl

int di[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dj[] = {1, -1, 0, 0, -1, 1, 1, -1};
string dir = "lrud";

const int n = 3;
vector<vi> arr(3 , vi(3));

struct HASH {
    ll operator()(const vector<vi> &v) const {
        ll ret = 0;
        for (int i = 0 ;i < n ;i++) {
            for (int j = 0 ;j < n ;j++) {
                ret *= 10;
                ret += v[i][j];
            }
        }
        return ret;
    }
};

unordered_map<vector<vi> , bool , HASH> vis ;
unordered_map<vector<vi> , vector<vi> , HASH> par ;

vector<vi> target = {{1 , 2 , 3} , {4 , 5 , 6} , {7 , 8 , 9}} , empty;

bool valid(int r , int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

bool path() {
    int r , c;
    for (int i = 0 ;i < n ;i++)
        for (int j = 0 ;j < n ;j++)
            if(arr[i][j] == 9)
                r = i , c = j;

    if(vis[arr]) {
        string path = "";
        while(par[arr] != empty) {
            for (int k = 0 ;k < 4 ;k++) {
                int nwr = r + di[k] , nwc = c + dj[k];
                if(valid(nwr , nwc) && par[arr][nwr][nwc] == 9) {
                    path += dir[k^1];
                    r = nwr , c = nwc;
                    arr = par[arr];
                    break;
                }
            }
        }

        for (int i = 0 ;i < path.size() ;i++)
            putchar(path[i]);
        puts("");

        return 1;
    }

    return 0;
}
void bfs2() {
    queue<vector<vi>> turn;
    vis[target] = 1;
    par[target] = empty;
    turn.push(target);

    int dep = 0;
    while(turn.size()) {
        int sz = turn.size();
        while(sz--) {
            vector<vi> cur = turn.front();
            turn.pop();

            int r , c;
            for (int i = 0 ;i < n ;i++)
                for (int j = 0 ;j < n ;j++)
                    if(cur[i][j] == 9)
                        r = i , c = j;


            for (int k = 0 ;k < 4 ;k++) {
                int nwr = r + di[k] , nwc = c + dj[k];
                if(valid(nwr , nwc)) {
                    vector<vi> nw = cur;
                    swap(nw[r][c] , nw[nwr][nwc]);
                    if(!vis[nw]) {
                        turn.push(nw) ;
                        vis[nw] = 1 ;
                        par[nw] = cur;
                    }
                }
            }
        }
        dep++;
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    scanf("%d",&T);

    bfs2();
    for (int test = 1 ; test <= T ;test++) {
        if(test != 1)
            puts("");


        char c;
        for (int i = 0 ;i < n ;i++) {
            for (int j = 0 ;j < n ;j++) {
                cin >> c;
                if(c == 'x')
                    arr[i][j] = 9;
                else
                    arr[i][j] = c - '0';
            }
        }


        if(!path())
            puts("unsolvable");
    }

}