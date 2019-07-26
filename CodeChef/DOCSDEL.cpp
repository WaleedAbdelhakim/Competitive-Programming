#include <bits/stdc++.h>

using namespace std;

int n , m;
vector<vector<int> > arr;

void solve () {
    long long info[450][450] = {};

    auto mul = [] (vector<int> &a , vector<int> &b) {
        vector<int> ret(m);
        for (int i = 0 ;i < m ;i++)
            ret[i] = b[a[i]];
        return ret;
    };

    for (int i = 0 ;i < n ;i++) {
        vector<int> a(m);
        iota(a.begin() , a.end() , 0);
        for (int j = i ;j < n ;j++) {
            a = mul(a , arr[j]);
            for (int k = 0 ;k < m ;k++)
                info[i][j] += (k + 1ll) * (a[k] + 1);
        }
    }

    int q , l , r;
    scanf("%d" , &q);
    while (q--) {
        scanf("%d%d" , &l , &r);
        printf("%lld\n" , info[l - 1][r - 1]);
    }
}

void solve2() {
    vector<vector<int> > pos(n , vector<int> (m));
    vector<int> chains;

    for (int j = 0 ;j < m ;j++) {
        int prev = j;
        for (int i = 0 ;i < n ;i++) {
            pos[i][prev] = chains.size();
            chains.push_back(arr[i][prev]);
            prev = arr[i][prev];
        }
    }

    int q , l , r;
    scanf("%d" , &q);
    while (q--) {
        scanf("%d%d" , &l , &r);
        l-- , r--;

        long long ans = 0;
        for (int i = 0 ;i < m ;i++)
            ans += (i + 1ll) * (chains[pos[l][i] + r - l] + 1);

        printf("%lld\n" , ans);
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T--) {
        scanf("%d%d" , &n , &m);
        arr = vector<vector<int> > (n , vector<int> (m));

        for (int i = 0 ;i < n ;i++)
            for (int j = 0 ;j < m ;j++)
                scanf("%d" , &arr[i][j]) , arr[i][j]--;
        n < m ? solve() : solve2();
    }
}