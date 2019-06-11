#include <bits/stdc++.h>
#define ones(n) __builtin_popcount(n)

using namespace std;

const int N = 30 , M = 26;
int n , needed[N] , nxt = 0;
map<int , int> val;
map<int , long long> memo;
set<int> exist;

void go(int node = 1) {
    if (exist.find(node) == exist.end()) return;
    go(node * 2);
    val[node] = nxt++;
    go(node * 2 + 1);
}

void go2(int node = 1 , int need = 0) {
    if (exist.find(node) == exist.end()) return;
    needed[val[node]] = need;
    go2(node * 2 , need | (1 << val[node]));
    go2(node * 2 + 1 , need | (1 << val[node]));
}

long long solve (int mask) {
    if (mask == (1 << n) - 1)
        return 1;

    if (memo.count(mask))
        return memo[mask];

    long long &ret = memo[mask];
    ret = 0;

    for (int i = 0 ;i < n ;i++)
        if (!(mask & (1 << i)) && (mask & needed[i]) == needed[i])
            ret += solve(mask | (1 << i));

    return ret;
}

class ConstructBST {
public:
    long long numInputs(vector <int> tree) {
        n = tree.size();
        exist = set<int>(tree.begin() , tree.end());
        go();
        go2();
        return solve(0);
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    ConstructBST test;
    cout << test.numInputs(
            {1, 3, 6});
}
