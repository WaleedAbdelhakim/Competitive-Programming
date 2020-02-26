#include <bits/stdc++.h>

using namespace std;

void run_case(long long n) {
    bool w = 1;
    while (n > 1) {
        if (w) {
            n = (n + 8) / 9;
        } else {
            n = (n + 1) / 2;
        }
        w = !w;
    }
    cout << (!w ? "Stan wins." : "Ollie wins.") << '\n';
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    
    long long n;
    while (cin >> n)
        run_case(n);
}