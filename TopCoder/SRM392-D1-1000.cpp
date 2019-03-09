/*
   explanation :
   i use boolean dp with state i(int) , g(bool) , f(vector<int>)
   it means , is there a way to fill the rightmost i + 1 digits knowing that 
   the number I'm currently forming is already  greater than the input if 
   g is 1 or still equal to it if g is 0, and having the frequency of each digit
   stored in f to determine at the end whether the number is equadigit or not

   the reason why this passes is that I ignore subproblems 
   that lead to invalid freq arrays, and the number of valid freq arrays is small.
   a valid freq array can't have a sum of frequencies greater than 19,
   and if we increased every non zero frequency to be equal to the maximum
   the sum of added values must be smaller than or equal to i + 1
   
   e.g. if the frequency array looks like this : 1 0 0 1 2 1 0 0 0 7 and i is 8
   the only hope for this number to be equadigit is for digits to equal at least 7
   21 digits needed and only 8 remaining, so that is not a valid freq array


   after that, we build the answer, if there was more than a choice you can put 
   in the current digit that leads to an equadigit number 
   go for the lowest one
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

const int N = 20;
map<vi , bool> memo[N][2];
class EquiDigitNumbers {
    string s;
    bool valid (int i , vi &v) {
        int mx = *max_element(v.begin() , v.end()) , rem = 0;
        for (int x : v) if (x) rem += mx - x;
        return rem <= i + 1;
    }

    bool is_equa(vi &v) {
        int mx = *max_element(v.begin() , v.end());
        for (int x : v)
            if (x != mx && x != 0)
                return 0;
        return 1;
    }

    int solve (int i , bool g , vi f) {
        if (!valid(i , f)) return 0;
        if (i < 0) return is_equa(f);

        if (memo[i][g].count(f))
            return memo[i][g][f];

        bool &ret = memo[i][g][f];
        int l = g ? 0 : s[i] - '0';
        int mx = *max_element(f.begin() , f.end());

        for (int j = l ;j <= 9 ;j++) {
            if (j || mx) f[j]++;
            if (solve(i - 1 , g || (j > l) , f)) return ret = 1;
            if (j || mx) f[j]--;
        }

        return ret = 0;
    }

    string build (int i , bool g , vi f) {
        if (i < 0) return "";
        int l = g ? 0 : s[i] - '0';
        int mx = *max_element(f.begin() , f.end());

        for (int j = l ;j <= 9 ;j++) {
            if (j || mx) f[j]++;
            if (solve(i - 1 , g || (j > l) , f))
                return ((j || mx) ? string(1 , char(j + '0')) : "") + build(i - 1 , g || (j > l) , f);
            if (j || mx) f[j]--;
        }
    }

public:
    ll findNext(string t) {
        s = t;
        reverse(s.begin() , s.end());
        s = s + string(N - s.size() - 1, '0');
        return stoll(build(N - 2 , 0 , vi(10 , 0)));
    }
};

int main() {
    EquiDigitNumbers test;
    cout << test.findNext("48");
}