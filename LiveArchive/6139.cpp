#include <bits/stdc++.h>
#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
using namespace std;

typedef vector<int> vi;
typedef long long ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 , -1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 1e5 + 5;
int n , q , s , e;
int arr[N];

struct Node{
    int negatives;
    bool zero;
} segTree[4 * N];

Node combine(Node a , Node b) {
    return {a.negatives + b.negatives , a.zero | b.zero};
}
void build(int l = 0 , int r = n - 1 , int pos = 1) {
    if(l == r) {
        segTree[pos] = {arr[l] < 0 , arr[l] == 0};
        return;
    }

    int mid = (l + r) / 2;
    build(l , mid , pos * 2);
    build(mid + 1 , r , pos * 2 + 1);
    segTree[pos] = combine(segTree[pos * 2] , segTree[pos * 2 + 1]);
}

void update(int ind ,int l = 0 , int r = n - 1 , int pos = 1) {
    if(l == r) {
        segTree[pos] = {arr[l] < 0 , arr[l] == 0};
        return;
    }

    int mid = (l + r) / 2;
    if(ind <= mid)
         update(ind , l , mid , pos * 2);
    if(ind > mid)
        update(ind , mid + 1 , r , pos * 2 + 1);

    segTree[pos] = combine(segTree[pos * 2] , segTree[pos * 2 + 1]);
}

Node query(int l = 0 , int r = n - 1 , int pos = 1) {
    if(l > e || r < s)
        return {0 , 0};
    if(l >= s && r <= e)
        return segTree[pos];
    int mid = (l + r) / 2;
    return combine(query(l , mid , pos * 2) , query(mid + 1 , r , pos * 2 + 1));
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    while(scanf("%d%d",&n,&q) == 2) {
        for (int i = 0 ;i < n ;i++)
            scanf("%d", arr + i);

        build();

        char type;
        int ind , value;
        while(q--) {
            scanf(" %c" , &type);
            if(type == 'C') {
                scanf("%d%d",&ind,&value);
                ind--;
                arr[ind] = value;
                update(ind);
            } else {
                scanf("%d%d",&s,&e);
                s-- , e--;
                Node res = query();
                if(res.zero)
                    printf("%c",'0');
                else if(res.negatives&1)
                    printf("%c",'-');
                else
                    printf("%c",'+');
            }
        }

        putchar('\n');
    }
}