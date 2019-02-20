#include <bits/stdc++.h>

using namespace std;
#define ones(n) __builtin_popcount(n)

const int MOD = 1e9 + 7 , N = 55 , M = 1 << 10 , O = 11;
int memo[N][M] , ways[O][O][2];

int mul (int a , int b) {
    return (a * 1ll * b) % MOD;
}

int add (int a , int b) {
    a += b;
    while (a >= MOD)
        a -= MOD;
    return a;
}

class MagicalGirlLevelTwoDivOne {
    vector<string> grid;
    int n , m , w , h;
public:
    int theCount(vector <string> palette, int nn , int mm) {
        grid = palette;
        n = palette.size();
        m = palette[0].size();
        h = nn , w = mm;
        pre();
        memset(memo , -1 , sizeof memo);
        return solve(0 , 0);
    }

    void pre() {
        for (int i = 0 ;i < h ;i++) {
            for (int j = 0 ;j < w ;j++) {
                ways[i][j][0] = ways[i][j][1] = 1;
                for (int ii = i ; ii < n ;ii += h) {
                    for (int jj = j ;jj < m ;jj += w) {
                        int d = grid[ii][jj] - '0';
                        if (grid[ii][jj] == '.') {
                            ways[i][j][0] = mul(ways[i][j][0] , 4);
                            ways[i][j][1] = mul(ways[i][j][1] , 5);
                        } else {
                            ways[i][j][0] = mul(ways[i][j][0] , (d+1)&1);
                            ways[i][j][1] = mul(ways[i][j][1] , d&1);
                        }
                    }
                }
            }
        }
    }

    int solve (int i , int mask) {
        if (i == h)
            return mask == (1 << w) - 1;

        int &ret = memo[i][mask];
        if (~ret)
            return ret;

        ret = 0;
        for (int m = 0 ;m < (1 << w) ;m++) {
            if (ones(m) % 2 == 0) continue;
            int W = 1;
            for (int j = 0 ;j < w ;j++) {
                bool bit = (1 << j) & m;
                W = mul(W , ways[i][j][bit]);
            }
            ret = add(ret , mul(W , solve(i + 1 , mask ^ m)));
        }

        return ret;
    }
};
