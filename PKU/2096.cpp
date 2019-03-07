#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

const int N = 1e3 + 5;
double memo[N][N];
int b , s;

double newP(int i , int a) {
    return (a - i - 0.0) / a;
}

double oldP(int i , int a) {
    return i * 1.0 / a;
}

double solve (int i , int j) {
    if (i > b || j > s || i == b && j == s)
        return 0;

    double &ret = memo[i][j];
    if (ret == ret)
        return ret;

    double diff = 0 , ps = oldP(i , b) * oldP(j , s);
    diff += newP(i , b) * newP(j , s) * (1 + solve(i + 1 , j + 1));
    diff += newP(i , b) * oldP(j , s) * (1 + solve(i + 1 , j));
    diff += newP(j , s) * oldP(i , b) * (1 + solve(i , j + 1));

    return ret = (diff + ps) / (1 - ps);
}

int main() {
    scanf("%d%d" , &s , &b);
    memset(memo , -1 , sizeof memo);
    printf("%.4f" , solve(0 , 0));
}