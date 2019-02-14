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

const int N = 1e5 , M = log2(N) , T = 1e6 + 5;
int n;
int arr[N] , table[N][M];
int Left[T] , Right[T];
void build(){
    for(int i = 0 ;i < n ;i++)
        table[i][0] = arr[i];

    for(int j = 1 ;j <= M ;j++)
        for(int i = 0 ;i + (1 << j) -1 < n ;i++)
            table[i][j] = min(table[i][j-1] , table[i + (1 << j-1)][j-1]);
}
int query(int l , int r){
    int k = log2(r - l + 1);
    return min(table[l][k] , table[r - (1 << k) + 1][k]);
}
int main(){
    while(scanf("%d",&n) == 1){
        for(int i = 0 ;i < n ;i++)
            scanf("%d" , arr + i);

        memset(Left , -1 , sizeof Left);
        memset(Right , -1 , sizeof Right);

        stack<int> s;
        for(int i = 1 ;i < n ;i++){
            while(s.size() && arr[i] >= arr[s.top()])
                s.pop();
            if(s.size())
                Left[i] = s.top();
            s.push(i);
        }

        s = stack<int>();
        for(int i = n-1 ;i >= 0 ;i--){
            while(s.size() && arr[i] >= arr[s.top()])
                s.pop();
            if(s.size())
                Right[i] = s.top();
            s.push(i);
        }

        build();

        bool f = 1;
        for(int i = 1 ;i < n-1 ;i++){
            if(!(arr[i] >= arr[i-1] && arr[i] >= arr[i+1])) continue;
            if(Right[i] == -1 && Left[i] == -1){
                if(arr[i] >= 150000){
                    if(!f)
                        printf(" ");
                    f = 0;
                    printf("%d",i+1);
                }
                continue;
            }

            int ret = -1;
            int l = Left[i] == -1 ? i : Left[i];
            if(Left[i] != -1)
                ret = max(ret , query(Left[i] , i));
            if(Right[i] != -1)
                ret = max(ret , query(i , Right[i]));

            if(arr[i] - ret >= 150000){
                if(!f)
                    printf(" ");
                f = 0;
                printf("%d",i+1);
            }
        }

        putchar('\n');
    }
}
