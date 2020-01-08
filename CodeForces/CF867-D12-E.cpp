#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int n;
    cin >> n;
    multiset<int> ms;

    long long ans = 0;
    while (n--) {
        int x;
        cin >> x;
        if (ms.size() && *ms.begin() < x) {
            ans += x - *ms.begin();
            ms.erase(ms.begin());
            ms.insert(x);
        }
        ms.insert(x);
    }

    cout << ans;
}