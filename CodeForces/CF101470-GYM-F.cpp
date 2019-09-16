#include <bits/stdc++.h>
 
using namespace std;
 
int n , k;
 
struct block {
    int lazy = 0;
    vector<pair<int , int> > v;
 
    void update() {
        lazy++;
    }
 
    void update(int l , int r) {
        for (int i = 0 ;i < v.size() ;i++)
            if (v[i].second >= l && v[i].second <= r)
                v[i].first++;
        sort(v.begin() , v.end());
    }
 
    int get(int x) {
        return upper_bound(v.begin() , v.end() , make_pair(x - lazy , (int)1e9)) - v.begin();
    }
 
    int get(int l , int r , int x) {
        //
    }
};
 
struct SqareRootDecompo {
    int bsz , bcnt;
    vector<block> blocks;
 
    SqareRootDecompo(vector<int> &a) {
        bsz = sqrt(a.size()) + 1;
        bcnt = (a.size() - 1) / bsz + 1;
        blocks = vector<block>(bcnt);
 
        for (int i = 0 ;i < a.size() ;i++)
            blocks[i / bsz].v.push_back({a[i] , i});
 
        for (int i = 0 ;i < bcnt ;i++)
            sort(blocks[i].v.begin() , blocks[i].v.end());
    }
 
    void update(int l , int r) {
        for (int i = l ;i <= r ;) {
            if (i % bsz == 0 && min(i + bsz - 1 , n - 1) <= r) {
                blocks[i / bsz].update();
                i += bsz;
            } else {
                int bid = i / bsz;
                blocks[bid].update(i , min(r , (bid + 1) * bsz - 1));
                i = (bid + 1) * bsz;
            }
        }
    }
 
    int query(int l , int r , int x) {
        int ret = 0;
        for (int i = l ;i <= r ;) {
            if (i % bsz == 0 && min(i + bsz - 1 , n - 1) <= r) {
                ret += blocks[i / bsz].get(x);
                i += bsz;
            } else {
                int bid = i / bsz;
                ret += blocks[bid].get(i , min(r , (bid + 1) * bsz - 1) , x);
                i = (bid + 1) * bsz;
            }
        }
        return ret;
    }
};
 
int main() {
    freopen("f.in", "r", stdin);
    while (scanf("%d%d" , &n , &k) , n + k) {
        vector<int> a(n);
        for (int i = 0 ;i < n ;i++)
            scanf("%d" , &a[i]);
 
        SqareRootDecompo sqd(a);
        sort(a.begin() , a.end());
 
        int l , r , med = a[(n + 1) / 2 - 1];
        while (k--) {
            scanf("%d%d" , &l , &r);
            sqd.update(l - 1 , r - 1);
            med += sqd.query(0 , n - 1 , med) < (n + 1) / 2;
            printf("%d\n" , med);
        }
    }
}