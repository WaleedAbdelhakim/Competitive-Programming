#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> arr , ans;

bool left() {
    queue<int> aval;
    for (int i = 0 ;i < arr.size() ;i++) {
        if (!~arr[i]) {
            aval.push(i);
            continue;
        }

        if (aval.size() < arr[i] - 1) return 0;

        for (int j = 0 ;j < arr[i] - 1;j++) {
            ans[aval.front()] = arr[i];
            aval.pop();
        }
    }

    return 1;
}

bool right() {
    queue<int> aval;
    for (int i = arr.size() - 1 ; ~i ;i--) {
        if (!~arr[i]) {
            aval.push(i);
            continue;
        }

        if (aval.size() < n - arr[i]) return 0;

        for (int j = 0 ;j < n - arr[i] ;j++) {
            ans[aval.front()] = arr[i];
            aval.pop();
        }
    }

    return 1;
}

int main() {
    scanf("%d" , &n);

    arr = ans = vector<int> (n * n , -1) ;

    int x;
    for (int i = 1 ;i <= n ;i++) {
        scanf("%d" , &x);
        arr[x - 1] = ans[x - 1] = i;
    }

    if (!left() || !right()) {
        puts("No");
        return 0;
    }

    puts("Yes");
    for (int i = 0 ;i < ans.size() ;i++)
        printf("%d " , ans[i]);
}