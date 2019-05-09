#include <bits/stdc++.h>

using namespace std;

const int M = 19 , N = 1 << M;
bool exist[N];

struct trie {
    vector<vector<int> > v;

    trie () {
        v.push_back(vector<int>(2 , -1));
    }

    void insert (int x) {
        int cur = 0;
        for (int i = M ;i >= 0 ;i--) {
            bool bit = x & (1 << i);
            if (v[cur][bit] == -1) {
                v[cur][bit] = v.size();
                v.push_back(vector<int>(2 , -1));
            }
            cur = v[cur][bit];
        }
    }

    int query(int x) {
        int cur = 0 , ret = 0;
        for (int i = M ;i >= 0;i--) {
            bool bit = x & (1 << i);
            if (~v[cur][bit])
                cur = v[cur][bit];
            else {
                cur = v[cur][!bit];
                assert(cur != -1);
                ret |= 1 << i;
            }
        }
        return ret;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int n , m , x;
    scanf("%d%d" , &n , &m);
    for (int i = 0 ;i < n ;i++)
        scanf("%d" , &x) , exist[x] = 1;

    trie t;
    for (int i = 0 ;i < N ;i++)
        if (!exist[i])
            t.insert(i);

    int cur = 0;
    while (m--) {
        scanf("%d" , &x);
        cur ^= x;
        printf("%d\n" , t.query(cur));
    }
}