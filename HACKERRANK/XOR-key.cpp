#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct node {
    int sum = 0;
    node *left, *right;
    node(int sum, node *left, node *right) : sum(sum), left(left), right(right) {}
    node(int sum = 0) : sum(sum), left(this), right(this) {}
};

node *insert(node *cur, int i , int v) {
    if (i == 0)
        return new node(cur->sum + 1);

    node *left = cur->left;
    node *right = cur->right;

    if (v & (1 << (i - 1)))
        left = insert(cur->left , i - 1, v);
    else
        right = insert(cur->right , i - 1, v);

    return new node(cur->sum + 1, left, right);
}

node *roots[N];

int query(node *bs, node *e , int i , int v) {
    if (i == 0)
        return 0;

    int leftCnt = e->left->sum - bs->left->sum;
    int rightCnt = e->right->sum - bs->right->sum;

    int j = i - 1;
    if (v & (1 << j)) {
        if (rightCnt) return (1 << j) + query(bs->right, e->right, i - 1, v);
        return query(bs->left , e->left , i - 1 , v);
    }

    if (leftCnt) return (1 << j) + query(bs->left , e->left , i - 1 , v);
    return query(bs->right, e->right, i - 1, v);
}


int main() {
    int T , n , q;
    scanf("%d" , &T);

    while (T--) {
        scanf("%d%d" , &n , &q);

        roots[0] = new node;
        int x;
        for (int i = 1 ;i <= n ;i++) {
            scanf("%d" , &x);
            roots[i] = insert(roots[i - 1] , 16 , x);
        }

        int l , r , a;
        while (q--) {
            scanf("%d%d%d" , &a , &l , &r);
            printf("%d\n" , query(roots[l - 1] , roots[r] ,  16 , a));
        }
    }
}
