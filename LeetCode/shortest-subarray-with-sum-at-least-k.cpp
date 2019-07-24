const int N = 5e4 + 5;
long long segTree[4 * N];

void in(int i , long long v , int l = 0 , int r = N - 1 , int pos = 1) {
    if (i > r || i < l) return;

    if (l == r) {
        segTree[pos] = v;
        return;
    }

    int mid = (l + r) / 2;
    in(i , v , l , mid , pos * 2);
    in(i , v , mid + 1 , r , pos * 2 + 1);

    segTree[pos] = min(segTree[pos * 2] , segTree[pos * 2 + 1]);
}

int query(long long v , int l = 0 , int r = N - 1 , int pos = 1) {
    if (l == r)
        return l;

    int mid = (l + r) / 2;
    if (segTree[pos * 2 + 1] <= v)
        return query(v , mid + 1 , r , pos * 2 + 1);

    return query(v , l , mid , pos * 2);
}

class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        memset(segTree , '?' , sizeof segTree);
        in(0 , 0);

        int len = A.size() + 1;
        long long sum = 0;
        for (int i = 0 ;i < A.size() ;i++) {
            sum += A[i];
            long long need = sum - K;
            if (segTree[1] <= need) len = min(len , i - query(need) + 1);
            in(i + 1 , sum);
        }

        return len == A.size() + 1 ? -1 : len;
    }
};