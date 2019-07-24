#include <bits/stdc++.h>

using namespace std;
using row = vector<long long>;
using mat = vector<row> ;

const int MOD = 1e9 + 7;

mat operator * (mat a , mat b) {
    mat ret = mat(a.size() , row(b[0].size()));
    for (int i = 0 ;i < ret.size() ;i++)
        for (int j = 0 ;j < ret[i].size() ;j++)
            for (int k = 0 ;k < ret[i].size() ;k++)
                ret[i][j] = (ret[i][j] + a[i][k] * b[k][j]) % MOD;
    return ret;
}

mat operator ^ (mat b , int p) {
    if (p == 1) return b;
    if (p&1) return b * (b ^ (p - 1));
    return (b * b) ^ (p / 2);
}

const int N = 105;
int f[N] ;

int main() {
    int n , t , x;
    scanf("%d%d" , &n , &x);
    for (int i = 0 ;i < n ;i++)
        scanf("%d" , &t) , f[t]++;

    mat a = mat(1 , row(101)) , b = mat(101 , row(101 , 0));

    a[0][100] = a[0][0] = 1;
    for (int i = 1 ;i <= min(x , 99) ;i++) {
        for (int j = 1 ;j <= i ;j++)
            a[0][i] = (a[0][i] + a[0][i - j] * f[j]) % MOD;
        a[0][100] = (a[0][100] + a[0][i]) % MOD;
    }

    if (x <= 99) {
        printf("%d" , a[0][100]);
        return 0;
    }


    for (int i = 0 ;i < 99 ;i++) b[i + 1][i] = 1;
    for (int i = 0 ;i < 100 ;i++) b[i][99] = b[i][100] = f[100 - i];
    b[100][100] = 1;


    printf("%d" , (a * (b ^ (x - 99)))[0][100]);
}
