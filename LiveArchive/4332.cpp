#include <bits/stdc++.h>

using namespace std;
using row = vector<long long>;
using mat = vector<row> ;

const int MOD = 10007;

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

int main() {
    int n;
    while (scanf("%d" , &n) , ~n) {
        mat m = {{1 , 2 , 1 , 4}} ;
        mat t = {{0 , 2 , 0 , 2} , {1 , 2 , 0 , 2} , {0 , 0 , 0 , 2} , {0 , 0 , 1 , 2}};

        if (n < 2) {
            printf("%d\n" , m[0][n + 2]);
            continue;
        }

        printf("%d\n" , (m * (t ^ (n - 1)))[0][3]);
    }
}