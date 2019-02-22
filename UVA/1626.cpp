#include <bits/stdc++.h>

using namespace std;

const int N = 105;
string s;
int memo[N][N];

char opp(char c) {
    switch(c) {
        case '(' : return ')';
        case '[' : return ']';
    }
}

int solve (int l , int r) {
    if (r < l)
        return 0;

    int &ret = memo[l][r];
    if (~ret)
        return ret;

    ret = solve(l + 1 , r) + 1;
    if (s[l] == '[' || s[l] == '(') {
        for (int j = l + 1 ;j <= r ;j++)
            if (s[j] == opp(s[l]))
                ret = min(ret , solve(l + 1 , j - 1) + solve(j + 1 , r));
    }

    return ret;
}

void path(int l , int r) {
    if (r < l)
        return;

    if (solve(l + 1 , r) + 1 == solve(l , r)) {
        if (s[l] == ')' || s[l] == '(')
            printf("()");
        else
            printf("[]");

        return path(l + 1 , r);
    }

    for (int j = l + 1 ;j <= r ;j++) {
        if (s[j] == opp(s[l]) && solve(l , r) == solve(l + 1 , j - 1) + solve(j + 1 , r)) {
            printf("%c" , s[l]);
            path(l + 1 , j - 1);
            printf("%c" , s[j]);
            path(j + 1 , r);
            return;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int T;
    scanf("%d" , &T);
    cin.ignore();
    while (T--) {
        cin.ignore();
        getline(cin , s);
        memset(memo , -1 , sizeof memo);
        path(0 , s.size() - 1);
        if (!T) puts("");
        else puts("\n");
    }

}
