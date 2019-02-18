// problem link : community.topcoder.com/stat?c=problem_statement&pm=10421&rd=14174
// solution idea :
// if there were no negative numbers we can solve this problem 
// using a simple pick or leave dp caring only about the maximum value
// but with negative numbers, you may regret going for the maximum
// since you can get two negative numbers with  product bigger than 
// what you would've got if you maximized
// so the key observation is that you need to get both maximum and minimum
// any choice in between is not logical

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;

const int N = 55;

struct info {
    ll mn , mx;
    bool valid;
    info (ll _mn = 0 , ll _mx = 0, bool _valid = 0) : mn(_mn) , mx(_mx) , valid(_valid) {}
};

info memo[N][N][N];
bool vis[N][N][N];

class TheProduct {
    vi arr;
    int d;
public:
    ll maxProduct(vi numbers, int k, int maxDist) {
        memset(vis, 0 , sizeof vis);
        arr = numbers;
        d = maxDist;
        return solve(0 , arr.size() , k).mx;
    }

    info solve (int i , int last , int rem) {
        if (i == arr.size() || !rem)
            return !rem ? info(1 , 1 , 1) : info(0 , 0 , 0);

        info &ret = memo[i][last][rem];
        if (vis[i][last][rem])
            return memo[i][last][rem];

        vis[i][last][rem] = 1;

        info ch1 , ch2;
        if (last == arr.size() || i < last + d)
            ch1 = solve(i + 1 , last , rem);

        if (rem)
            ch2 = solve(i + 1 , i , rem - 1);

        ch2.mn *= arr[i];
        ch2.mx *= arr[i];
        if (ch2.mn > ch2.mx)
            swap(ch2.mn , ch2.mx);

        if (ch1.valid && ch2.valid)
            return ret = info(min(ch2.mn , ch1.mn) , max(ch2.mx , ch1.mx) , 1);

        return (ret = ch1.valid ? ch1 : ch2);
    }
};

