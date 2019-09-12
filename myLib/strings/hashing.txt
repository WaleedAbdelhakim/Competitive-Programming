#include <bits/stdc++.h>
using namespace std;

const int B1 = 256;
const int B2 = 128;
const int MOD1 = 2000000011;
const int MOD2 = 1000000007;

const int N = 1e6 + 6;
char str[N];
pair<int, int> prefix[N];
pair<int, int> suffix[N];

void hash_prefix(){
    int h1 , h2;
    h1 = h2 = 0;
    for(int i = 0 ; str[i] ; i++){
        h1 = ((1LL * h1 * B1) %MOD1 +str[i]) %MOD1;
        h2 = ((1LL * h2 * B2) %MOD2 +str[i]) %MOD2;
        prefix[i] = make_pair(h1,h2);
    }
}

void hash_suffix(){
    int h1 , h2 , pw1 , pw2;
    h1 = h2 = 0;
    pw1 = pw2 = 1;
    int sz = strlen(str);
    for(int i = sz-1 ; i>=0;i--){
        h1 = (h1 + (1LL * pw1 * str[i])%MOD1 )%MOD1;
        h2 = (h2 + (1LL * pw2 * str[i])%MOD2 )%MOD2;
        pw1 = (1LL*pw1*B1)%MOD1;
        pw2 = (1LL*pw2*B2)%MOD2;
        suffix[i] = make_pair(h1,h2);
    }
}
