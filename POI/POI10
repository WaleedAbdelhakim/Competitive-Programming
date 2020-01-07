#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 5e3 + 5 , M = 5e4 + 5;
int a[N] , done[M] , dist[M];

struct path {
    int to , cost;
    bool operator < (const path &other) const {
        return cost > other.cost;
    }
};

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
    int n , mn = M;
    cin >> n;

    for (int i = 0 ;i < n ;i++) {
        cin >> a[i];
        mn = min(mn , a[i]);
    }

    memset(dist , '?' , sizeof dist);
    priority_queue<path> q;
    q.push({0 , a[0]});
    dist[0] = 0;

    while (q.size()) {
        int mod = q.top().to;
        q.pop();

        if (done[mod]) continue;
        done[mod] = 1;

        for (int i = 0 ;i < n ;i++) {
            int new_mod = (mod + a[i]) % mn;
            if (dist[new_mod] > dist[mod] + a[i]) {
                dist[new_mod] = dist[mod] + a[i];
                q.push({new_mod , dist[new_mod]});
            }
        }
    }


    int m;
    cin >> m;

    while (m--) {
        int x;
        cin >> x;
        if (dist[x % mn] <= x)
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
}