#include <bits/stdc++.h>
#include <math.h>
#define pb push_back
#define INF 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long   ll;

const int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
const int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 181;
int comp[N] , perm[N];
bool vis[N][N][N] = {0};

void pre_calc(){
   set<int> rep = {0 , 50};
   for(int i = 1 ;i <= 20 ;i++)
        rep.insert(i) , rep.insert(i*2) , rep.insert(i*3);

   vi info(rep.begin() , rep.end());

   for(int a : info){
        for(int b : info){
            for(int c : info){
                if(a + b + c >= N)continue;
                perm[a + b + c]++;
                vi t = {a , b , c};
                sort(all(t));
                if(!vis[t[0]][t[1]][t[2]])
                    comp[a + b + c]++ , vis[t[0]][t[1]][t[2]] = 1;
            }
        }
   }
}
int main(){
    int n;

    pre_calc();

    while(scanf("%d",&n) , n > 0){
        if(comp[n] && n < N){
            printf("NUMBER OF COMBINATIONS THAT SCORES %d IS %d.\n",n , comp[n]);
            printf("NUMBER OF PERMUTATIONS THAT SCORES %d IS %d.\n" , n , perm[n]);
        }else
            printf("THE SCORE OF %d CANNOT BE MADE WITH THREE DARTS.\n" , n);

        printf("%s\n",string(70 , '*').c_str());
    }
    puts("END OF OUTPUT");
}
