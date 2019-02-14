#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 1e9
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;

const int N = 1005 ;
int a , b , n;

pair<int , int> f(int first,int second ,bool t){return !t ? mp(a , second) : mp(first , b);}
pair<int , int> e(int first ,int second,bool t){return !t ? mp(0 , second) : mp(first , 0);}
pair<int , int> p(int first ,int second,bool t){
    if(!t)
        return {first - (min(second + first , b) - second) , min(second + first , b)};
    else
        return {min(second + first , a) , second - (min(second + first , a) - first)};
}

pair<int , int> (*funcs[3])(int,int ,bool) = {f , e , p};
string op[] = {"fill" , "empty" , "pour"};
string which[][] = {{"A" , "B"} , {"A" , "B"} , {"A B" , "B A"}};

void print(pair<int , int> cur , map<pair<int , int> , pair<int , int> > &papa){
    if(cur == mp(0 , 0))
        return;

    auto parent =  papa[cur];
    for(int i = 0 ;i < 3 ;i++){
        for(int j = 0 ;j < 2 ;j++){
            pair<int , int> t = funcs[i](parent.first , parent.second , j);
            if(t == cur){
                print(parent , papa);
                cout<<op[i] << " " << which[i][j]<<endl;
                return ;
            }
        }
    }
}
void bfs(){
    bool vis[N][N] = {0};
    map<pair<int,int> , pair<int ,int> > papa;
    queue<pair<int , int> > turn;

    turn.push({0 , 0});
    vis[0][0] = 1;

    pair<int , int> cur;
    int sz = 1;
    bool stop = 0;
    for(;turn.size();sz = turn.size()){
        while(sz--){
            cur = turn.front();
            turn.pop();

            if(cur.second == n){
                stop = 1;
                break;
            }

            for(int i = 0 ;i < 3 ;i++){
                for(int j = 0 ;j < 2 ;j++){
                    pair<int , int> t = funcs[i](cur.first , cur.second , j);
                    if(!vis[t.first][t.second]){
                        turn.push(t);
                        vis[t.first][t.second] = 1 ;
                        papa[t] = cur;
                    }
                }
            }

        }
        if(stop)
            break;
    }

    print(cur , papa);
    puts("success");
}
int main(){
    while(scanf("%d%d%d",&a,&b,&n) == 3){
        bfs();
    }
}
