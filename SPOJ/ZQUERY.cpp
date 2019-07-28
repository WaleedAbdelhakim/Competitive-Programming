// editorial to a very similer problem 
// discuss.codechef.com/t/qchef-editorial/10123

#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 5, M = 5e4 + 5;
int n, q;
int arr[N], st[M], en[M], ind[M], ans[M];

int segTree[4 * N] , f[N];
deque<int> dq[2 * N];

void upd(int i , int d , int l = 0 , int r = n, int pos = 1) {
    if (i < l || i > r) return ;
    segTree[pos] += d;
    if (l == r) return;
    int mid = (l + r) / 2;
    upd(i , d , l , mid , pos * 2);
    upd(i , d , mid + 1 , r , pos * 2 + 1);
}

int get_max(int l = 0 , int r = n, int pos = 1) {
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (segTree[pos * 2 + 1]) return get_max(mid + 1 , r , pos * 2 + 1);
    return get_max(l , mid , pos * 2);
}

void add_len(int e) {
    if (!dq[e].size()) return;
    int l = dq[e].back() - dq[e].front();
    if (!f[l]) upd(l , 1);
    f[l]++;
}

void remove_len(int e) {
    if (!dq[e].size()) return;
    int l = dq[e].back() - dq[e].front();
    f[l]--;
    if (!f[l]) upd(l , -1);
}

void add(int i) {
    remove_len(arr[i]);
    if (!dq[arr[i]].size() || i < dq[arr[i]].front())
        dq[arr[i]].push_front(i);
    else
        dq[arr[i]].push_back(i);
    add_len(arr[i]);
}

void remove(int i) {
    remove_len(arr[i]);
    if (dq[arr[i]].front() == i)
        dq[arr[i]].pop_front();
    else
        dq[arr[i]].pop_back();
    add_len(arr[i]);
}

void mo() {
    int bsz = ceil(sqrt(n));
    sort(ind, ind + q, [bsz](int i, int j) {
        int ibid = st[i] / bsz, jbid = st[j] / bsz;
        return tie(ibid, en[i]) < tie(jbid, en[j]);
    });

    int s = 0, e = -1;
    for (int j = 0; j < q; j++) {
        int i = ind[j];

        while (e < en[i])
            add(++e);
        while (s < st[i])
            remove(s++);
        while (s > st[i])
            add(--s);
        while (e > en[i])
            remove(e--);

        ans[i] = get_max();
    }
}

int main() {
    scanf("%d%d" , &n , &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d" , arr + i);
        arr[i] += arr[i - 1];
    }

    for (int i = 0 ;i <= n ;i++)
        arr[i] += N;

    for (int i = 0; i < q; i++) {
        scanf("%d%d" , st + i , en + i);
        st[i]--;
        ind[i] = i;
    }

    mo();

    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i]);
}