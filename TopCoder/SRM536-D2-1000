#include <bits/stdc++.h>

using namespace std;


const int N = 55;
double memo[N];

class MergersDivTwo {
    vector<int> rev;
    int k;
    double solve (int i) {
        double &ret = memo[i];
        if (ret == ret)
            return ret;

        ret = 0;
        for (int j = 0 ;j <= i ;j++)
            ret += rev[j] / (i + 1.0);

        int sum = 0 , cnt = 1;
        for (int j = i ;j >= k ; j--) {
            cnt++ , sum += rev[j];
            if (j <= i - k + 2)
                ret = max(ret , (sum + solve(j - 1))  / cnt);
        }

        return ret;
    }
public:
    double findMaximum(vector<int> revenues, int kk) {
        rev = revenues;
        sort(rev.begin() , rev.end());
        k = kk;
        memset(memo , -1 , sizeof memo);
        return solve(rev.size() - 1);
    }
};

int main() {
    MergersDivTwo test;
    cout << test.findMaximum({5, -7, 3}
    ,2);
}