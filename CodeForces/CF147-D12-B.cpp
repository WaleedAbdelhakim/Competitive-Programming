#include <bits/stdc++.h>

using namespace std;
using row = vector<int>;
using mat = vector<row> ;

mat operator * (mat a , mat b) {
    mat ret = a;
    for (int i = 0 ;i < ret.size() ;i++)
        for (int j = 0 ;j < ret[i].size() ;j++)
            for (int k = 0 ;k < ret[i].size() ;k++)
                ret[i][j] = max(ret[i][j] , a[i][k] + b[k][j]);
    return ret;
}

mat operator ^ (mat b , int p) {
    if (p == 1) return b;
    if (p&1) return b * (b ^ (p - 1));
    return (b * b) ^ (p / 2);
}

bool good(mat a) {
    for (int i = 0 ;i < a.size() ;i++)
        if (a[i][i] > 0)
            return 1;
    return 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r"  ,stdin);
#endif
    int n , m;
    scanf("%d%d" , &n , &m);

    mat a = mat(n , row(n , -1e9));
    for (int i = 0 ;i < n ;i++) a[i][i] = 0;
    mat cur = a;

    int i , j , ij , ji;
    while (m--) {
        scanf("%d%d" , &i , &j);
        scanf("%d%d" , &a[i - 1][j - 1] , &a[j - 1][i - 1]);
    }

    if (!good(a ^ n)) {
        puts("0");
        return 0;
    }

    mat info[10];
    info[0] = a;
    for (int i = 1 ;i < 9 ;i++)
        info[i] = info[i - 1]  * info[i - 1];

    int ans = 0;
    for (int i = 8 ; ~i ;i--)
        if (!good(cur * info[i]))
            cur = cur * info[i] , ans += 1 << i;

    printf("%d" , ans + 1);
}
