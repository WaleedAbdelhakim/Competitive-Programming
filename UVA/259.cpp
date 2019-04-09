#include <bits/stdc++.h>

using namespace std;


const int N = 250; // max man node
const int M = 11; // max woman node
vector<int> adj[N];
int husband[M] , vis[N] , vid;
bool find_match(int node) {
    if (vis[node] == vid)
        return 0;

    vis[node] = vid;
    for (int child : adj[node]) {
        if (husband[child] == -1 || find_match(husband[child])) {
            husband[child] = node;
            return 1;
        }
    }

    return 0;
}

string men;
int max_match() {
    memset(husband , -1 , sizeof husband);
    int cnt = 0;
    for (int i = 0 ;i < men.size() ;i++) { // loop over men
        ++vid;
        cnt += find_match(i);
    }
    return cnt;
}

void init() { // every test case
    for (int i = 0 ;i < N ;i++)
        adj[i].clear();
    men = "";
}

void go(string a , string b) {
    for (int i = 0 ;i < a[1] - '0' ;i++) {
        for (int j = 0 ;j < b.size() - 1 ;j++)
            adj[men.size()].push_back(b[j] - '0');
        men += a[0];
    }
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif

    string a , b;
    while (getline(cin , a)) {
        init();
        stringstream f(a);
        f >> a >> b;
        go(a , b);
        while (getline(cin , a) , a != "") {
            stringstream t(a);
            t >> a >> b;
            go(a , b);
        }

        if (max_match() == men.size()) {
            for (int i = 0 ;i < 10 ;i++) {
                if (husband[i] != -1)
                    cout << men[husband[i]];
                else
                    cout << '_';
            }
            cout << '\n';
        } else
            cout << "!\n";
    }
}