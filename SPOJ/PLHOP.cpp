#include <bits/stdc++.h>

using namespace std;
using row = vector<long long>;
using mat = vector<row> ;

mat operator * (mat a , mat b) {
    mat ret = mat(a.size() , row(b[0].size()));
    for (int i = 0 ;i < ret.size() ;i++) {
        for (int j = 0 ;j < ret[i].size() ;j++) {
            ret[i][j] = 1e18;
            for (int k = 0 ;k < ret[i].size() ;k++)
                ret[i][j] = min(ret[i][j] , a[i][k] + b[k][j]);
        }
    }
    return ret;
}

mat operator ^ (mat b , int p) {
    if (p == 1) return b;
    if (p&1) return b * (b ^ (p - 1));
    return (b * b) ^ (p / 2);
}

int main() {
    int T , n , k;
    scanf("%d" , &T);
    for (int t = 1 ; t <= T ; t++) {
        scanf("%d%d" , &k , &n);

        mat d(n , row(n));
        for (int i = 0 ;i < n ;i++)
            for (int j = 0 ;j < n ;j++)
                scanf("%lld" , &d[i][j]);

        mat org = d;
        d = d ^ k;

        for (int r = 0 ; r < n ; r++)
            for (int i = 0 ;i < n ;i++)
                for (int j = 0 ;j < n ;j++)
                    d[i][j] = min(d[i][j] , org[i][r] + d[r][j]);

        printf("Region #%d:\n" , t);
        for (int i = 0 ;i < n ;i++)
            for (int j = 0 ;j < n ;j++)
                printf("%lld%c" , d[i][j] , " \n"[j == n - 1]);

        puts("");
    }


}