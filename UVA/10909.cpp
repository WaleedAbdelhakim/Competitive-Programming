    #include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 1e9
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;

const int N = 2e6 ,M = 4194304;
int interval[M] = {0};

void in(int num ,int s = 1 ,int e = N ,int p = 1){
    interval[p]++;
    if(s == e) return;
    if(num <= (s+e)/2)
        return in(num , s , (s+e)/2 , p*2);
    in(num ,(s+e)/2+1 , e , p*2+1);
}
int getkth(int kth ,int s = 1 ,int e = N ,int p = 1){
    if(kth > interval[p])
        return -1;
    if(s == e)return s;
    if(kth <= interval[p*2])
        return getkth(kth ,s , (s+e)/2 , p*2);
    return getkth(kth - interval[p*2] , (s+e)/2+1 , e , p*2+1);
}
void del(int num ,int s = 1 ,int e = N ,int p = 1){
    interval[p]--;
    if(s == e) return;
    if(num <= (s + e) / 2)
        del(num ,s , (s+e)/2 , p*2);
    else
        del(num ,(s+e)/2+1 , e , p*2+1);
}
int main(){
    for(int i = 1 ;i < N ;i+=2)
        in(i);

    int next = 2 , value;
    bool l[N] = {0};
    vi lucky = {1};
    l[1] = 1;

    while((value = getkth(next++)) != -1){
        lucky.pb(value);
        l[value] = 1;
        vi info;
        int cur;
        for(int i = value;(cur = getkth(i)) != -1;i += value)
            info.pb(cur);
        for(auto x : info)
            del(x);
    }

    int q;
    while(cin >> q){
        bool found = 0 ;
        if(q&1){
            printf("%d is not the sum of two luckies!\n",q);
            continue;
        }

        int ind = lower_bound(all(lucky) , q / 2) - lucky.begin();
        for(int i = ind;i >= 0;i--){
            if(l[q-lucky[i]]){
                printf("%d is the sum of %d and %d.\n",q,min(lucky[i] , q-lucky[i]),max(q-lucky[i] , lucky[i]));
                found = 1;
                break;
            }
        }

        if(!found)
            printf("%d is not the sum of two luckies!\n",q);
    }
}
