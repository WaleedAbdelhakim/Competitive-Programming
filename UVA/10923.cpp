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

const int n = 9 , m = 8;

struct state {
    string arr[n];
};

int Count(const state &cur ,pair<int , int> &me) {
    int ret = 0;
    for (int i = 0 ;i < n ;i++) {
        for (int j = 0 ;j < m ;j++) {
            ret += cur.arr[i][j] == 'E';
            if(cur.arr[i][j] == 'S')
                me.first = i , me.second = j;
        }
    }
    return ret;
}

bool valid(int r , int c , const state &s) {
    return r >= 0 && r < n && c >= 0 && c < m && s.arr[r][c] == '.';
}

void move(state &s ,int r , int c) {
    vector<pair<int , int > > info;
    for (int i = 0 ;i < n ;i++)
        for (int j = 0 ;j < m ;j++)
            if(s.arr[i][j] == 'E')
                info.pb({i , j}) , s.arr[i][j] = '.';

    for (auto &x : info) {
        int nwr = x.first + (r > x.first) - (r < x.first);
        int nwc = x.second + (c > x.second) - (c < x.second);
        if(s.arr[nwr][nwc] == 'E')
            s.arr[nwr][nwc] = '#';
        else if(s.arr[nwr][nwc] != '#')
            s.arr[nwr][nwc] = 'E';
    }
}

bool bfs(state s ) {
    queue<state> turn;
    turn.push(s);
    int dep = 0;
    while(turn.size()) {
        int sz = turn.size();
        while(sz--) {
            state cur = turn.front();
            turn.pop();
            pair<int , int> me = {-1 , -1};


            int cnt = Count(cur , me);

            if(me.first == -1) continue;
            if(!cnt)
                return 1;


            for (int k = 0 ;k < 8 ;k++) {
                int nwr = me.first + di[k];
                int nwc = me.second + dj[k];
                if(valid(nwr , nwc , cur)) {
                    state nw = cur;
                    nw.arr[me.first][me.second] = '.';
                    nw.arr[nwr][nwc] = 'S';
                    move(nw , nwr , nwc);
                    turn.push(nw);
                }
            }
        }
        dep++;
    }

    return 0;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    scanf("%d",&T);

    while(T--) {
        state f;
        for (int i = 0 ;i < n ;i++)
            cin >> f.arr[i];

        puts(bfs(f ) ? "I'm the king of the Seven Seas!" : "Oh no! I'm a dead man!");
    }
}