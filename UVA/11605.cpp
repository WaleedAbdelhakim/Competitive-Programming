#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

struct mat{
    static const int M = 2;
    double a[M][M];
    mat(bool v = 0){
        memset(a, 0, sizeof a);
        for(int i = 0; i < M; i++)  a[i][i] = v;
    }
    double* operator[](int idx){
        return a[idx];
    }
    mat operator *(mat &b){
        mat ans;
        for(int i = 0; i < M; i++)
            for(int k = 0; k < M; k++)
                for(int j = 0; j < M; j++)
                    ans[i][j] = (ans[i][j] + a[i][k] * 1ll * b[k][j]);
        return ans;
    }
};

mat operator ^(mat a, int b){
    mat ans(1);
    for( ; b; b >>= 1, a = a * a)
        if(b & 1)
            ans = ans * a;
    return ans;
}

void run_case(int t) {
    int n , m , p , k;
    cin >> n >> m >> p >> k;

    long long all = n * n * p * p * 1ll * m * m;

    double ans = 0;
    for (int i = 1 ;i <= n ;i++) {
        int cnti = i * (n - i + 1) * 2 - 1;
        for (int j = 1 ;j <= m ;j++) {
            int cntj = j * (m - j + 1) * 2 - 1;
            for (int h = 1 ;h <= p ;h++) {
                int cnth = h * (p - h + 1) * 2 - 1;
                long long my_sub_grids = cnti * cntj * 1ll * cnth;
                double in = 1.0 * my_sub_grids / all;
                double out = 1 - in;
                mat t;
                t.a[0][1] = t.a[1][0] = in;
                t.a[0][0] = t.a[1][1] = out;
                ans += (t ^ k)[0][1];
            }
        }
    }

    cout << "Case " << t << ": " << fixed << setprecision(10) << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
    int t;
    cin >> t;
    for (int i = 1 ;i <= t ;i++)
        run_case(i);
}