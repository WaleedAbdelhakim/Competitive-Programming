#include <bits/stdc++.h>

using namespace std;

int l[6] , r[6];

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int n;
    scanf("%d" , &n);
    for (int i = 0 ;i < n ;i++)
        scanf("%d%d" , l + i , r + i);

    double exp = 0;
    for (int v = 1 ;v <= 1e4 ;v++) {
        double prob = 0;
        for (int i = 0 ;i < n ;i++) {
            if (v > r[i]) continue;
            for (int j = 0 ;j < n ;j++) {
                if (j == i || v < l[j] || v > r[j]) continue;
                double p = (r[i] - max(v + (i > j), l[i]) + 1.0) / (r[i] - l[i] + 1);
                p *= 1.0 / (r[j] - l[j] + 1);
                for (int k = 0 ;k < n ;k++) {
                    if (k == i || k == j) continue;
                    p *= max(0 , min(v - (j > k) , r[k]) - l[k] + 1) / (r[k] - l[k] + 1.0);
                }
                prob += p;
            }
        }
        exp += prob * v;
    }

    printf("%.9f" , exp);
}