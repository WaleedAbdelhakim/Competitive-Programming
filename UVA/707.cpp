/*
   let can[x] be the set of possible cells for the robber at time x. 
   initially can[x] contains all cells that lie on none of the messages at time x.
   knowing that the robber can move at most one unit per time step , 
   we can update can[x] according to can[x - 1] and can[x + 1].

   if cell (x , y) is in can[x] then there must be cell in can[x - 1] 
   that is one step far from it, as well as in can[x + 1]

   if for some x can[x] is empty that means the robber escaped.
   if can[x] has one cell then the robber's location can be deduced at time x.
   if for all sets no set has exactly one cell then there is nothing known.
*/


#include <bits/stdc++.h>

using namespace std;

int di[] = {0, 0, 1, -1};
int dj[] = {1, -1, 0, 0};

const int N = 105;
int n , m , O ;
bool can[N][N][N] , susb[N][N] , temp[N][N];
int X[N] , Y[N];

void init() {
    memset(can , 1 , sizeof can);
    memset(susb , 1 , sizeof susb);
    memset(X , -1 , sizeof X);
    memset(Y , -1 , sizeof Y);
}

bool get(int i , int j) {
    int cnt = susb[i][j];
    for (int k = 0 ;k < 4 ;k++) {
        int nwi = i + di[k] , nwj = j + dj[k];
        cnt += (nwi >= 0 && nwi < n && nwj >= 0 && nwj < m) && susb[nwi][nwj];
    }
    return cnt;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in" , "r" , stdin);
#endif
    int test = 1;
    while (scanf("%d%d%d" , &m , &n ,&O) , m+n+O) {
        init();

        int s , mom , l , t , r , b;
        scanf("%d" , &s);
        while (s--) {
            scanf("%d%d%d%d%d" , &mom , &l , &t , &r , &b);
            for (int i = t ;i <= b ;i++)
                for (int j = l ;j <= r ;j++)
                    can[mom - 1][i - 1][j - 1] = 0;
        }

        vector<int> moments(O);
        iota(moments.begin() , moments.end(), 0);
        for (int i = O - 2 ;i >= 0 ;i--) moments.push_back(i);

        bool escaped = 0 , fact = 0;
        for (int x : moments) {
            for (int i = 0 ;i < n ;i++) {
                for (int j = 0 ;j < m ;j++) {
                    can[x][i][j] &= get(i , j);
                    temp[i][j] = can[x][i][j];
                }
            }

            int cnt = 0 , ir , jr;
            for (int i = 0 ;i < n ;i++) {
                for (int j = 0 ;j < m ;j++) {
                    susb[i][j] = temp[i][j];
                    if (susb[i][j]) ir = i , jr = j , cnt++;
                }
            }

            if (cnt == 1) X[x] = ir + 1, Y[x] = jr + 1, fact = 1;
            escaped = cnt == 0;
        }

        printf("Robbery #%d:\n" , test++);
        if (escaped)
            puts("The robber has escaped.");
        else if (!fact)
            puts("Nothing known.");
        else {
            for (int x = 0 ;x < O ;x++)
                if (~X[x])
                    printf("Time step %d: The robber has been at %d,%d.\n" , x + 1 , Y[x] , X[x]);
        }

        puts("");
    }
}