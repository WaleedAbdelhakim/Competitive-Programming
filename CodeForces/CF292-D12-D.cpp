#include <bits/stdc++.h>

using namespace std;

struct DSU{
    vector<int> par, size;
    int CC;
    DSU(int n){
        CC = n;
        par.resize(n+1);
        size.assign(n+1, 1);
        iota(par.begin(), par.end(), 0);
    }
    int root(int a){
        return par[a] == a ? a: par[a] = root(par[a]);
    }
    void unite(int a,int b){
        a = root(a);
        b = root(b);
        if(a == b) return;
        if(size[a] < size[b]) swap(a,b);

        par[b] = a;
        size[a] += size[b];
        --CC;
    }
    bool same(int a,int b){
        return root(a) == root(b);
    }
};

const int N = 1e4 + 5;
int a[N] , b[N];

int main() {
    int n , m , st  , en;
    scanf("%d%d" , &n , &m);
    for (int i = 0 ;i < m ;i++)
        scanf("%d%d" , a + i, b + i);

    int q;
    scanf("%d" , &q);
    while (q--) {
        scanf("%d%d" , &st , &en);
        DSU dsu(n);
        for (int i = 0 ;i < st - 1 ;i++)
            dsu.unite(a[i] , b[i]);
        for (int i = en ;i < m ;i++)
            dsu.unite(a[i] , b[i]);

        printf("%d\n" , dsu.CC);
    }
}