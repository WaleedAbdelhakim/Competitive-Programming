#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;

map<string , vector<string> > adj;
map<string , bool> vis;
map<string , int> group;

void dfs(string word ,int g){
    vis[word] = 1 , group[word] = g;
    for(string s : adj[word])
        if(!vis[s])
            dfs(s , g);
}
int main(){
    string a , b;

    map<string , bool> words;
    vector<string> info;
    while(cin>>a && a != "--"){
        words[a] = 1;
        info.pb(a);
    }

    for(int i = 0 ;i < info.size() ;i++){
        for(int j = 0 ;j < info[i].length() ;j++){
            for(int k = 'a' ;k <= 'z' ;k++){
                string t = info[i];
                if(k == t[j])continue;
                t[j] = k;
                if(words[t]){
                    adj[t].pb(info[i]);
                    adj[info[i]].pb(t);
                }
            }
            for(int k = 'A' ;k <= 'Z' ;k++){
                string t = info[i];
                if(k == t[j])continue;
                t[j] = k;
                if(words[t]){
                    adj[t].pb(info[i]);
                    adj[info[i]].pb(t);
                }
            }
        }
    }
    int g = 1;
    for(int i = 0 ;i < info.size() ;i++){
        if(!vis[info[i]])
            dfs(info[i] , g++);
    }
    while(cin>>a>>b){
        if(group[a] == group[b])
            puts("Yes");
        else
            puts("No");
    }
}
