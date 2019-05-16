#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int arr[N];
map<int , int> f;

int main() {
    int n;
    long long k;
    scanf("%d%lld" , &n , &k);
    for (int i = 0 ;i < n ;i++)
        scanf("%d" , arr + i) , f[arr[i]]++;

    sort(arr, arr + n);

    for (auto p : f) {
        if (p.second * 1ll * n < k)
            k -= p.second * 1ll * n;
        else {
            int kk = p.second;
            for (int i = 0 ;i < n ;i++) {
                if (k > kk)
                    k -= kk;
                else {
                    printf("%d %d" , p.first , arr[i]);
                    return 0;
                }
            }
        }
    }
}
