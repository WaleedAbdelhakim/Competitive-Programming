#include <bits/stdc++.h>

using namespace std;

const int N = 205;
int n;
int x[N] , y[N];
double mx[N][N];

double dist(int i , int j) {
    int dx = x[i] - x[j];
    int dy = y[i] - y[j];
    return sqrt(dx * dx + dy * dy);
}

void floyd() {
    for (int i = 0 ;i < n ;i++)
        for (int j = 0 ;j < n ;j++)
            mx[i][j] = dist(i , j);

    for (int k = 0 ;k < n ;k++)
        for (int i = 0 ;i < n ;i++)
            for (int j = 0 ; j < n ;j++)
                mx[i][j] = min(mx[i][j] , max(mx[i][k] , mx[k][j]));
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int test = 1;
    while (scanf("%d" , &n) , n) {
        for (int i = 0 ;i < n ;i++)
            scanf("%d%d" , x + i , y + i);

        floyd();

        printf("Scenario #%d\nFrog Distance = %.3f\n\n" , test++ , mx[0][1]);
    }
}