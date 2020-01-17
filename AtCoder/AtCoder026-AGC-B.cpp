#include <bits/stdc++.h>

using namespace std;

void run_case() {
    long long A , B , C , D;
    cin >> A >> B >> C >> D;
    if (A < B || D < B) {
        cout << "No\n";
        return;
    }

    if (C >= B) {
        cout << "Yes\n";
        return;
    }

    long long g = __gcd(D , B);
    long long mx = B - g + A % g;

    cout << (mx > C ? "No\n" : "Yes\n");
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
    int t;
    cin >> t;
    while (t--)
        run_case();
}
