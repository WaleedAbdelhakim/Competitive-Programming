#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 500 + 5;
int n , m , q;
int arr[N][N];

int main(){
    while(scanf("%d %d",&n,&m) , (n || m)){
        for(int i = 0 ;i < n ;i++)
            for(int j = 0 ;j < m ; j++)
                scanf("%d",&arr[i][j]);

        scanf("%d",&q);
        int mn , mx;
        while(q--){
            scanf("%d%d",&mn,&mx);
            int ans = 0;
            for(int i = 0 ;i < m ;i++){
                int l = 0 , r = n-1 , pos = -1, mid , len = -1;
                while(l <= r){
                    mid = (l + r) / 2;
                    if(arr[mid][i] >= mn){
                        pos = mid;
                        r = mid-1;
                    }else
                        l = mid+1;
                }

                if(pos == -1 || arr[pos][i] > mx) continue;

                l = 1 , r = min(m - i , n - pos);
                while(l <= r){
                    mid = (l + r) / 2;
                    if(arr[pos+mid-1][i+mid-1] <= mx){
                        len = mid;
                        l = mid+1;
                    }else
                        r = mid-1;
                }

                ans = max(ans , len);
            }
            printf("%d\n",ans);
        }
        puts("-");
    }


}
