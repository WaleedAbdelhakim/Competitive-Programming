#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

//template<typename T>
//using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef vector<int> vi;
typedef unsigned long long ll;

#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
#define watch(x) cout << (#x) << " is " << (x) << endl

int di[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dj[] = {1, -1, 0, 0, -1, 1, 1, -1};

const int N = 2e5 + 5;
int n;
int arr[N], segTree[4 * N];

void build(int l = 0, int r = n - 1, int pos = 1) {
    if (l == r) {
        segTree[pos] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, pos * 2);
    build(mid + 1, r, pos * 2 + 1);
    segTree[pos] = segTree[pos * 2] + segTree[pos * 2 + 1];
}

void Set(int i, int value, int l = 0, int r = n - 1, int pos = 1) {
    if(i > r || i < l)
        return;
    if(l == r) {
        segTree[pos] = value;
        return;
    }
    int mid = (l + r) / 2;
    Set(i , value , l , mid , pos * 2);
    Set(i , value , mid + 1 , r , pos * 2 + 1);
    segTree[pos] = segTree[pos * 2] + segTree[pos * 2 + 1];
}

int query(int s , int e , int l = 0 , int r = n - 1 , int pos = 1) {
    if(l > e || r < s)
        return 0;
    if(l >= s && r <= e)
        return segTree[pos];
    int mid = (l + r) / 2;
    return query(s , e , l , mid , pos * 2) + query(s , e , mid + 1 , r , pos * 2 + 1);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int test = 1;
    while (scanf("%d", &n) , n != 0) {
        for (int i = 0; i < n; i++)
            scanf("%d", arr + i);

        build();

        if(test != 1)
            puts("");

        printf("Case %d:\n",test++);

        char op[4];
        int f , s;
        while (scanf("%s",op) , strcmp(op , "END") != 0) {
            scanf("%d%d",&f,&s);
            if(strcmp(op , "S") == 0)
                Set(f - 1 , s);
            else
                printf("%d\n" , query(f - 1 , s - 1));
        }
    }
}