#include <bits/stdc++.h>

using namespace std;

template<typename T>
vector<int> sort_cyclic_shifts(const T &s) { 
    int n = s.size();
    const int alphabet = 1e6 + 5; 
    vector<int> p(n) , g(n) , cnt(max(n , alphabet) , 0);

    for (int i = 0 ;i < n ;i++) cnt[s[i]]++;
    for (int i = 1 ;i < alphabet ;i++) cnt[i] += cnt[i - 1];
    for (int i = 0 ;i < n ;i++) p[--cnt[s[i]]] = i;

    g[p[0]] = 0;
    int groups = 1;
    for (int i = 1 ;i < n ;i++) {
        groups += (s[p[i - 1]] != s[p[i]]);
        g[p[i]] = groups - 1;
    }

    vector<int> pn(n) , gn(n);
    for (int h = 0 ; (1 << h) < n ;h++) {
        fill(cnt.begin() , cnt.begin() + groups , 0);

        for (int i = 0 ;i < n ;i++) pn[i] = (p[i] - (1 << h) + n) % n; 
        for (int i = 0 ;i < n ;i++) cnt[g[pn[i]]]++; 
        for (int i = 1 ;i < groups ;i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1 ;i >= 0 ;i--) p[--cnt[g[pn[i]]]] = pn[i];

        gn[p[0]] = 0;
        groups = 1;
        for (int i = 1 ;i < n ;i++) {
            groups += tie(g[p[i]] , g[(p[i] + (1 << h)) % n])
                      != tie(g[p[i - 1]] , g[(p[i - 1] + (1 << h)) % n]);
            gn[p[i]] = groups - 1;
        }
        g = gn;
    }

    return p;
}

template <typename T>
vector<int> build_lcp(T const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;

    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}

template <typename T>
vector<int> suffix_array_construction(T s) {
    s.push_back(*min_element(s.begin() , s.end()) - 1);
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

const int N = 2e5 + 5, M = 19;
int nxt[N] ;
long long dp[N];

void pre(vector<int> &a) {
    dp[a.size()] = 0;
    for (int i = a.size() - 1 ;i >= 0 ;i--) {
        int j = i + 1;
        while (j < a.size() && a[j] <= a[i])
            j = nxt[j];
        nxt[i] = j;
        dp[i] = (nxt[i] - i) * 1ll * a[i] + dp[nxt[i]];
    }
}

int table[M][N] , LG[N];
void build(vector<int> &a) {
    for (int i = 0 ;i < N ;i++)
        table[0][i] = i;

    for (int j = 1; j <= M; j++) {
        for (int i = 0; i + (1 << j) - 1 < a.size(); i++) {
            int f = table[j - 1][i];
            int s = table[j - 1][i + (1 << (j - 1))];
            table[j][i] = a[f] > a[s] ? f : s;
        }
    }
}

int Max(int l, int r , vector<int> &a) {
    int lg = LG[r - l + 1];
    int f = table[lg][l];
    int s = table[lg][r - (1 << lg) + 1];
    return a[f] > a[s] ? f : s;
}

void init() {
    LG[0] = -1;
    for (int i = 1; i < N; i++)
        LG[i] = LG[i - 1] + !(i - (i & (-i)));
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    init();
    int T , n;
    scanf("%d" , &T);
    while (T--) {
        scanf("%d" , &n);

        vector<int> a(n);
        for (int i = 0 ;i < n ;i++)
            scanf("%d" , &a[i]);

        vector<int> p = suffix_array_construction(a);
        vector<int> lcp = build_lcp(a , p);
        pre(a);
        build(a);

        long long ans = 0;
        for (int i = 0 ;i < p.size() ;i++) {
            if (i && lcp[i - 1]) {
                int last = p[i] + lcp[i - 1] - 1;
                int max_ind = Max(p[i] , last , a);
                ans += (nxt[max_ind] - last - 1) * 1ll * a[max_ind] + dp[nxt[max_ind]];
            } else {
                ans += dp[p[i]];
            }
        }

        printf("%lld\n" , ans);
    }
}