#include <bits/stdc++.h>

using namespace std;

const int N = 105;
int n, m;
int a[N], b[N] , ans[N][N];

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);

    for (int i = 0; i < m; i++)
        scanf("%d", b + i);

    for (int bit = 0; bit < 30; bit++) {
        vector<int> r, c;
        for (int i = 0; i < n; i++)
            if ((1 << bit)&a[i])
                r.push_back(i);

        for (int j = 0; j < m; j++)
            if ((1 << bit)&b[j])
                c.push_back(j);

        int diff = abs((int)r.size() - (int)c.size());
        int mn = min(r.size() , c.size());

        if (diff % 2 != 0) {
            puts("NO");
            return 0;
        }

        int i = 0;
        while (i < r.size() && i < c.size())
            ans[r[i]][c[i]] |= (1 << bit) , i++;

        if (r.size() < c.size())
            for (;i < c.size() ;i++)
                ans[0][c[i]] |= (1 << bit);

        if (r.size() > c.size())
            for (;i < r.size();i++)
                ans[r[i]][0] |= (1 << bit);
    }

    puts("YES");
    for (int i = 0 ;i < n ;i++) {
        for (int j = 0 ;j < m ;j++)
            printf("%d " , ans[i][j]);
        puts("");
    }
}