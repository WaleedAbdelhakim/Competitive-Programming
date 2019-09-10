#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5 , M = 1e6 + 6;
int n;
int a[N] , par[N] , val[M];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d" , &n);
    for (int i = 0 ;i < n ;i++)
        scanf("%d" , a + i);

    set<pair<int , int> > info;
    info.insert({0, 1e9});

    auto get = [&](int x) {
        info.erase({val[x + 1] , x + 1});
        if (x) info.erase({val[x - 1] , x - 1});
        auto ret = *info.rbegin();
        info.insert({val[x + 1] , x + 1});
        if (x) info.insert({val[x - 1] , x - 1});
        return ret;
    };

    auto update = [&](int x , int v) {
        info.erase({val[x] , x});
        val[x] = v;
        info.insert({val[x] , x});
    };

    for (int i = n - 1 ;i >= 0 ;i--) {
        auto mn = get(a[i]);
        par[i] = mn.second;
        update(a[i] , mn.first + 1);
    }

    auto nxt = *info.rbegin();
    printf("%d\n" , n - nxt.first);
    for (int i = 0 ;i < n ; i++) {
        if (a[i] == nxt.second) {
            while (i < n && a[i] == nxt.second)
                printf("%d " , nxt.second) , i++;
            i--;
            nxt.second = par[i];
        }
    }
}