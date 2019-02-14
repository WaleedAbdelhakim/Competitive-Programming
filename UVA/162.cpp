#include <bits/stdc++.h>
#include <math.h>
#define pb push_back
#define INF 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long   ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

map<char , int> photo = {{'A' , 4} , {'K' , 3} , {'Q' , 2} , {'J' , 1}};
deque<char> f , s , ground;

void go(bool player ,int cnt ,bool photoCame){
    for(int i = 0 ;i < cnt ;i++){
        if(player){
            if(f.size()){
                ground.pb(f.back());
                f.pop_back();
                if(photo.count(ground.back()))
                    return go(!player , photo[ground.back()] , 1);
            }else{
                printf("%d%3d\n",(!player)+1 , s.size());
                return  ;
            }
        }else{
            if(s.size()){
                ground.pb(s.back());
                s.pop_back();
                if(photo.count(ground.back()))
                    return go(!player , photo[ground.back()] , 1);
            }else{
                printf("%d%3d\n",(!player)+1, f.size());
                return;
            }
        }
    }
    if(photoCame){
        while(ground.size()){
            if(player)
                s.push_front(ground.front());
            else
                f.push_front(ground.front());

            ground.pop_front();
        }
    }
    go(!player , 1 , 0);
}
int main(){
    string card;
    while(cin >> card && card != "#"){
        f.pb(card[1]);
        for(int i = 1 ;i <= 51 ;i++){
            cin >> card;
            if(i % 2)
                s.pb(card[1]);
            else
                f.pb(card[1]);
        }
        go(1 , 1 , 0);
        f.clear() , s.clear() , ground.clear();
    }
}

