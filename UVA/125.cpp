#include <bits/stdc++.h>

using namespace std;

const int N = 55 ;
int n;
int paths[N][N];

void floyd() {
    for (int k = 0 ;k < n ;k++)
        for (int i = 0 ;i < n ;i++)
            for (int j = 0 ;j < n ;j++)
                paths[i][j] += paths[i][k] * paths[k][j];
}

bool cycle(int s , int d) {
    for (int i = 0 ;i < n ;i++)
        if (paths[i][i] && paths[s][i] && paths[i][d])
            return 1;
    return 0;
}

void init() {
    n = 0;
    memset(paths , 0 , sizeof paths);
}

int main() {
    int m , u , v , test = 0;
    while (scanf("%d" , &m) == 1) {
        init();
        while (m--) {
            scanf("%d%d" , &u , &v);
            paths[u][v]++;
            n = max(n , max(u + 1 , v + 1));
        }

        floyd();

        printf("matrix for city %d\n" , test++);
        for (int i = 0 ;i < n ;i++)
            for (int j = 0 ;j < n ;j++)
                printf("%d%c" , cycle(i , j) ? -1 : paths[i][j] , " \n"[j == n - 1]);
    }
}