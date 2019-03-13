#include <bits/stdc++.h>

using namespace std;


const int N = 500;
int n;
bool e[N][N];
vector<string> info;
map<string , int> ind;

void init() {
    memset(e , 0 , sizeof e);
    ind.clear();
    info.clear();
}

void floyd() {
    for (int k = 0 ;k < info.size() ;k++)
        for (int i = 0 ;i < info.size() ;i++)
            for (int j = 0 ;j < info.size() ;j++)
                e[i][j] |= e[i][k] && e[k][j];
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int test = 1;
    while (cin >> n , n) {
        init();
        int c , m;
        string a , b;
        for (int i = 0 ;i < n ;i++) {
            cin >> c;
            for (int i = 0 ;i < c ;i++) {
                cin >> a;
                if (i)
                    e[info.size() - 1][info.size()] = 1;
                ind[a] = info.size();
                info.push_back(a);
            }
        }

        cin >> m;
        while (m--) {
            cin >> a >> b;
            e[ind[a]][ind[b]] = 1;
        }

        floyd();

        vector<pair<int , int> > ans;
        for (int i = 0 ;i < info.size() ;i++)
            for (int j = i + 1 ;j < info.size() ;j++)
                if (!(e[i][j] + e[j][i]))
                    ans.push_back({i , j});

        if (ans.size()) {
            cout << "Case " << test++ << ", " << ans.size() << " concurrent events:\n";
            for (int i = 0 ;i < min((int)ans.size() , 2) ;i++)
                cout << (i ? " " : "") << '(' << info[ans[i].first] << ',' << info[ans[i].second] << ')';
            cout << '\n';
        } else
            cout << "Case " << test++ << ", no concurrent events.\n";
    }
}