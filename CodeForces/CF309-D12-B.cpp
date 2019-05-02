#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 6 , M = 20;
int n , r , c;
string arr[N];
int cu[N] , par[N][M];

void build() {
    for (int i = 0 ;i < N ;i++)
        for (int j = 0 ;j < M ;j++)
            par[i][j] = i;

    for (int i = 1 ;i <= n ;i++) {
        int l = i , r = n , theOne = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (cu[mid] - cu[i - 1] + mid - i <= c)
                theOne = mid , l = mid + 1;
            else
                r = mid - 1;
        }
        if (~theOne)
            par[i][0] = theOne + 1;
    }
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    cin >> n >> r >> c;
    for (int i = 1 ;i <= n ;i++) {
        cin >> arr[i];
        cu[i] = cu[i - 1] + arr[i].size();
    }
    build();

    int mx = 0 , theOne = -1;
    for (int i = n ;i >= 1 ;i--) {
        for (int j = 1 ;j < M ;j++)
            par[i][j] = par[par[i][j - 1]][j - 1];

        int p = i;
        for (int j = 0 ;j < M ;j++)
            if (r & (1 << j))
                p = par[p][j];

        if (p - i > mx)
            mx = p - i , theOne = i;
    }


    for(int j = 0 ;j < r && theOne <= n && arr[theOne].size() <= c; j++ , theOne = par[theOne][0]) {
        for (int i = theOne ;i < par[theOne][0] ;i++)
            cout << arr[i] << (i == par[theOne][0] - 1 ? "\n" : " ");
    }
}