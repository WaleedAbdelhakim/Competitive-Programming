#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;

const int N = 755;
int n;
int a[N] , b[N];

struct info {
    int val , ind;
    bool operator < (const info &other) const {
        return val > other.val;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    while (scanf("%d" , &n) == 1) {
        for (int i = 0 ;i < n ;i++)
            scanf("%d" , a + i);

        for (int i = 1 ;i < n ;i++) {
            priority_queue<info> pq;
            for (int j = 0 ;j < n ;j++)
                scanf("%d" , b + j);

            sort(b , b + n);
            for (int j = 0 ;j < n ;j++)
                pq.push({a[j] + b[0] , 0});

            for (int j = 0 ;j < n ;j++) {
                a[j] = pq.top().val;
                pq.push({pq.top().val - b[pq.top().ind] + b[pq.top().ind + 1] , pq.top().ind + 1});
                pq.pop();
            }
        }

        for (int i = 0 ;i < n ;i++)
            printf("%d%c" , a[i] , " \n"[i == n - 1]);
    }
}