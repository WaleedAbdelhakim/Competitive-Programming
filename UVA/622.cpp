/*
 you need to check 4 things to determine whether the inupt is valid or not
 1 - every char must be a digit or one of these chars "()*+"
 2 - if we removed every thing other than brackets
 we will end up with a regular bracket sequence
 3 - any number has no leading zeros
 4 - any input that is not valid, must have one of these cases in it
 "()" , ")(" , "(+" , "+)" , "(*" , "*)" , "+*" , "*+"
 or a digit with "(" after it
 or ")" with a digit after it

 as it is not allowed to have * or + at the end or at the begin of the input too
 so we will make input equal to '(' + input + ')'
*/


/*
 evaluation
 it is very easy to evaluate a simple sequence
 that only have digits and '*' and '+' in linear time
 to handle the brackets we will make a recursive function that takes an index
 and starting from that index it will keep moving forward
 and calculating until reaching any closing bracket
 in case of reaching an open bracket
 we will recursively calculate what in that bracket
 and continue after the close of this bracket
 in any call when we reach a close bracket
 we will return evaluation of the bracket
 and the index of the close bracket + 1
 for the previous bracket to continue
*/


#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define val first
#define ind second

string s, allowed = "()*+";
string erorr[] = {"()" , ")(" , "(+" , "+)" , "(*" , "*)" , "+*" , "*+"};

bool valid() {
    int opened = 0 , first = 1;
    for (int i = 0; i < s.size(); i++) {
        opened += s[i] == '(';
        opened -= s[i] == ')';

        if (i + 1 < s.size()) {
            string t = s.substr(i , 2);
            for (int j = 0 ;j < 8 ;j++) if (t == erorr[j]) return 0;
            if (isdigit(s[i]) && s[i + 1] == '(') return 0;
            if (isdigit(s[i + 1]) && s[i] == ')') return 0;
        }

        if (!isdigit(s[i]) && allowed.find(s[i]) == -1) return 0;
        if (opened < 0) return 0;
        if (s[i] == '0' && first && i + 1 < s.size() && isdigit(s[i + 1])) return 0;
        first = !isdigit(s[i]);
    }

    return opened == 0;
}

pair<ll, int> evaluate(int i) {
    int st = i;
    ll total = 0, pro = 1 , temp;
    while (s[i] != ')') {
        temp = 0;
        int cnt = 0;
        while (isdigit(s[i])) {
            cnt++;
            temp = temp * 10 + s[i] - '0';
            i++;
        }

        if (cnt) pro *= temp;

        if (s[i] == '(') {
            auto c = evaluate(i + 1);
            pro *= c.val;
            i = c.ind;
        }

        if (s[i] == '+'){
            total += pro;
            pro = 1;
        }

        i += s[i] != ')';
    }
    return {total + pro , i + 1};
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> s;
        s = "(" + s + ")";

        if (!valid()) {
            cout << "ERROR\n";
            continue;
        }

        cout << evaluate(1).val << '\n';
    }
}