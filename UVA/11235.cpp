#include <bits/stdc++.h>
#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef pair<int , int> ii;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 2e5 + 5 , K = log2(N);
int sparse_table[N][K];
vi rep;

void build(){
    for(int i = 0 ;i < rep.size() ;i++)
        sparse_table[i][0] = rep[i];

    for(int j = 1 ;j <= K ;j++)
        for(int i = 0 ;i + (1 << j) - 1 < rep.size() ;i++)
            sparse_table[i][j] = max(sparse_table[i][j-1] , sparse_table[i + (1 << j-1)][j-1]);

}
int query(int l , int r){
    int j = log2(r - l + 1);
    return max(sparse_table[l][j] , sparse_table[r - (1 << j) + 1][j]);
}
int main(){
    int n , q;
    while(scanf("%d %d" ,&n,&q) == 2){
        map<int , int> first_occ , last_occ , pos;
        int arr[n];
        for(int i = 0 ;i < n ;i++)
            scanf("%d" , arr + i) , last_occ[arr[i]] = i;

        for(int i = n-1 ;i >= 0 ;i--)
            first_occ[arr[i]] = i;

        rep.clear();
        int v = arr[0] , r = 1;
        for(int i = 1 ;i < n ;i++){
            if(arr[i] == v)
                r++;
            else{
                rep.pb(r);
                pos[v] = rep.size()-1;
                v = arr[i];
                r = 1;
            }
        }
        rep.pb(r);
        pos[v] = rep.size()-1;
        build();

        int a , b;
        while(q--){
            scanf("%d %d",&a,&b);
            a-- , b--;
            if(arr[a] == arr[b]){
                printf("%d\n" , b - a + 1);
                continue;
            }
            int l = arr[upper_bound(arr , arr+n , arr[a]) - arr];
            int r = arr[(lower_bound(arr , arr+n , arr[b]) - arr) - 1];
            int mx = max(b-first_occ[arr[b]] + 1 , last_occ[arr[a]] - a + 1);
            if(r < l){
                printf("%d\n" , mx);
                continue;
            }
            printf("%d\n",max(query(pos[l] , pos[r]) , mx));
        }
    }
}
