#include <bits/stdc++.h>

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    long long x;
    scanf("%lld" , &x);

    vector<pair<long long , long long> > info;

    long long p = 0 , s = 0;
    for (long long n = 1 ;; n++) {
        long long m = (x - p + n * s) / (s + n);
        if (m < n) break;
        if ((x - p + n * s) % (s + n) == 0) {
            info.push_back({n , m});
            if (n != m)
                info.push_back({m , n});
        }
        p += n * n;
        s += n;
    }

    sort(info.begin() , info.end());

    printf("%d\n" , info.size());
    for (int i = 0 ;i < info.size() ;i++)
        printf("%lld %lld\n" , info[i].first , info[i].second);

}