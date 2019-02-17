#include <bits/stdc++.h>

using namespace std;

const int N = 1005 , MOD = 1e9 + 7;
int n;
int grid[3][N];

int mul (int a , int b) {
    a *= b;
    if (a >= MOD)
        a -= MOD;

    return a;
}

int main() {
    int T;
    scanf("%d" , &T);

    for (int c = 1 ; c <= T ; c++) {
        scanf("%d" , &n);

        char ch;
        for (int i = 0 ;i < 3 ;i++) {
            for (int j = 0 ;j < n ;j++) {
                scanf(" %c" , &ch);
                grid[i][j] = ch == '#';
            }
        }


        if (n&1 || grid[1][1] + grid[0][0] + grid[1][0]) {
            printf("Case #%d: %d\n" , c , 0);
            continue;
        }

        int cur = 1 , ans = 1;
        while (1) {
            if (cur == n - 1) {
                ans *= !grid[2][n - 1];
                break;
            }

            int options = grid[0][cur] + grid[0][cur + 1] == 0;
            options += grid[2][cur] + grid[2][cur + 1] == 0;
            options *= grid[1][cur + 1] + grid[1][cur + 2] == 0;

            ans = mul(ans , options);
            cur += 2;
        }

        printf("Case #%d: %d\n" , c , ans);
    }
}