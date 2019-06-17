#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int mul(int a , int b) {
    return a * 1ll * b % MOD;
}

int add (int a , int b) {
    a += b;
    while (a >= MOD)
        a -= MOD;
    return a;
}

int sum(int n) {
    return mul(mul(n , n + 1) , 500000004);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int a , b;
    scanf("%d%d" , &a, &b);
    printf("%d" , mul(sum(b - 1) , add(a , mul(b , sum(a)))));
}