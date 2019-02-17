// explanation:
// 1 - # of columns has to be even
// 2 - the only case we have more than one choice 
// is if the flow is at a cell in the second row
// and you got to it through it's left side 
// choices are gonna be up and down
// and whatever choice you make you will have only one choice 
// until you reach a similar cell
// so if you are at (2, x) and you got to it through (2, x - 1)
// you are gonna have at most two ways to get to (2 , x + 2)
// and you can count them by checking if there is an obstacle in either of them
// let w[x] be a number >= 0 and <= 2 and it denotes
// the number of ways to go from x to x + 2
// the final answer is w[2] * w[4] * w[6] * ... * w[n]
// and as we start our calculations from col 2
// we have to make sure we can reach it in the first place 

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