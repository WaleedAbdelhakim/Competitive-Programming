#include <bits/stdc++.h>

using namespace std;

const int N = 16;
string names[N];
double beat[N][N] , p[N] , t_p[N];

void go (int l , int r) {
    if (l == r) {
        p[l] = 1;
        return;
    }

    int mid = (l + r) / 2;
    go(l , mid);
    go(mid + 1 , r);

    for (int i = l ;i <= mid ; i++) {
        t_p[i] = 0;
        for (int j = mid + 1 ;j <= r ;j++)
            t_p[i] += p[j] * beat[i][j];

        t_p[i] *= p[i];
    }

    for (int i = mid + 1 ;i <= r ; i++) {
        t_p[i] = 0;
        for (int j = l  ;j <= mid ;j++)
            t_p[i] += p[j] * beat[i][j];

        t_p[i] *= p[i];
    }

    for (int i = l ;i <= r ;i++)
        p[i] = t_p[i];
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);

    for (int i = 0 ;i < N ;i++)
        cin >> names[i];

    for (int i = 0 ;i < N ;i++) {
        for (int j = 0 ;j < N ;j++) {
            int x;
            cin >> x;
            beat[i][j] = x / 100.0;
        }
    }

    go(0 , N - 1);

    for (int i = 0 ;i < N ;i++)
        cout << names[i] << setw(13 - names[i].size()) << "p=" << fixed << setprecision(2) << p[i] * 100 << '%' << '\n';

}