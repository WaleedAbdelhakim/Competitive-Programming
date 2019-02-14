#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};


int main(){
    int n , T = 1;
    while(scanf("%d",&n) , n){
        vi info(n) , sorted(n);
        for(int i = 0 ;i < n ;i++)
            scanf("%d",&info[i]) , sorted[i] = info[i];

        sort(all(sorted));

        map<vi , bool> vis;
        queue<pair<string , vi> > turn;
        turn.push({"" , info});

        int cnt = 0 ;
        while(turn.size() && !cnt){
            int sz = turn.size();
            while(sz--){
                string mp = turn.front().first;
                vi v = turn.front().second;
                vis[v] = 1;

                turn.pop();
                if(v == sorted && mp != "")
                    cnt++;


                if(!cnt){
                    for(int i = 1 ;i < v.size() ;i++){
                        swap(v[i] , v[i-1]);
                        if(!vis[v])
                            turn.push({mp + char(i+'0') , v});
                        swap(v[i] , v[i-1]);
                    }
                }
            }
        }

        printf("There are %d swap maps for input data set %d.\n",cnt, T++);
    }
}
