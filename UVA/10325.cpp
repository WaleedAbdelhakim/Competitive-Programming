#include <bits/stdc++.h>

using namespace std;

const int N = 16;
int n , m;
int arr[N];

long long LCM(long long a , long long b) {
    return a / __gcd(a , b) * b;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    while (scanf("%d%d" , &n , &m) == 2) {
        for (int i = 0 ;i < m ;i++)
            scanf("%d" , arr + i);

        int c = 0;
        for (int i = 1 ;i < (1 << m) ;i++) {
            long long lcm = 1 ;
            int cnt = 0;
            for (int j = 0 ;j < m && lcm < n ;j++)
                if (i & (1 << j))
                    lcm = LCM(lcm , arr[j]) , cnt++;

            if (cnt&1)
                c += n / lcm;
            else
                c -= n / lcm;
        }

        printf("%d\n" , n - c);
    }
}