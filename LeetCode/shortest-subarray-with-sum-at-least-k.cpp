// problem :
//      given an array with positive and negative values 
//      find the shortest subarray with sum at least k
// solution :
//      let p[i] be the sum of all elements in (i)th prefix with p[0] (the empty prefix) begin equal to 0 
//      we will iterate over every possible end of a subarray e in range [1 , n]
//      we know that the sum of subarray [l , r] is equal to p[r] - p[l - 1]
//      for every possible start s in range [1 , e] we will call it good if p[e] - p[s - 1] >= k
//      so to be a good start p[s - 1] has to be at most p[e] - k
//      now among all good starts we need to find the one with the maximum index

//      so our new problem is given an array consider all elements  with value <= x
//      and get the rightmost one 
//      we can do this using segment tree 
//      initially every element in the array is initialized to a large value greater than x will ever be 
//      to not be considered in the search for the best start
//      and as we go through possible ends from left to right we will update a[i] with p[i]
//      to be considered as a possible start

//      the way we will find the best start for the current e is that we will start at the root which is in charge of the whole array 
//      we will ask if the min in right half is at most x then we go right
//      otherwise we go left, we do this until we reach a leaf then return its index
//      there might not be any good starts, we can check for that by asking about the minimum of the hole array

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
